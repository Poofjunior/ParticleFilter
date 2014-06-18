/**
 * laserScanner.hpp
 * \author Joshua Vasquez
 * \date June 12, 2014
 */

#include "laserScanner.hpp"

LaserScanner::LaserScanner(float angleSpread, size_t numPoints)
:angleSpread_{angleSpread}, numPoints_{numPoints}
{
    // Create the array for scan distances:
    scan_ = new float[numPoints];
    step_ = angleSpread / (numPoints - 1);
}


LaserScanner::~LaserScanner()
{
    delete [] scan_;
}

void LaserScanner::takeScan(Pose& pose, Map& map)
{
    std::cout << std::endl;
    float angleToMeas = pose.theta_ - (angleSpread_/2);
    Point intersection;
    Point scanPt(pose.x_, pose.y_); 
    std::cout << "scanPt: " << scanPt.x_ << ", " << scanPt.y_ << std::endl;
    Point segStart, segEnd;
    float distToSeg;
    float minDistSoFar = std::numeric_limits<float>::infinity();
    std::list<Point>::iterator nextPtIter;

    // For all angles, for all map segs, get closest wall dist. 
    for(size_t beamIndex = 0; beamIndex < numPoints_; ++beamIndex)
    {
        std::cout << "angleToMeas: " << angleToMeas << std::endl;
        // Find minimum with a best-so-far iteration method.
        minDistSoFar = std::numeric_limits<float>::infinity();

        // Nested for-loop to iterate through all points via their features
        for (auto featureIter = map.features_.begin(); 
             featureIter != map.features_.end(); ++featureIter)
        {
            for (auto ptIter = featureIter->points_.begin();  
                 ptIter != featureIter->points_.end(); ++ptIter)
            {
                // Check for forward-connectedness between two adjacent pts.
                if (ptIter->forwardConnected_)
                {
                    segStart = *ptIter;
                    // Check if last point is forwardConnected to first point.
                    nextPtIter = ptIter;
                    ++nextPtIter;
                    segEnd = *nextPtIter;
                    
                    if(nextPtIter == featureIter->points_.end())
                        segEnd = featureIter->points_.front();

                    getIntersection(intersection, scanPt, angleToMeas,  
                                    segStart, segEnd); 

                    std::cout << "segStart: (" << segStart.x_ << "," 
                              << segStart.y_ 
                              << ") segEnd: (" << segEnd.x_ << ", " 
                              << segEnd.y_ << ")"
                              << std::endl;

                    distToSeg = getDist(scanPt, intersection);

                    if (distToSeg < minDistSoFar)
                        minDistSoFar = distToSeg;
                }
            }
        }
        scan_[beamIndex] = minDistSoFar; 
        angleToMeas += step_;
    }
    
}

float LaserScanner::getDist(Point& pt1, Point& pt2)
{
    return sqrt( (pow( (pt1.x_ - pt2.x_), 2) + 
                  pow( (pt1.y_ - pt2.y_), 2)));
}

void LaserScanner::getIntersection(Point& intersection, 
                                   Point& scanPt, 
                                   float scanAngle, 
                                   Point& segStart, Point& segEnd)
{
    float scannerM = round(tan(CommonMath::tuneAngle(scanAngle)));
    float segmentM = (segEnd.y_ - segStart.y_)/(segEnd.x_ - segStart.x_);
    
    if (CommonMath::parallel(scannerM, segmentM))
    {
        intersection.x_ = std::numeric_limits<float>::infinity(); 
        intersection.y_ = std::numeric_limits<float>::infinity(); 
        return;
    }
    
    float yInt;
    if (scannerM == std::numeric_limits<float>::infinity()) 
    {
        yInt = segmentM * (-segStart.x_) + segStart.y_;
        intersection.x_ = scanPt.x_;
        intersection.y_ = segmentM * scanPt.x_ + yInt;
    }
    else if (segmentM == std::numeric_limits<float>::infinity()) 
    {
        yInt = scannerM * (-scanPt.x_) + scanPt.y_;
        intersection.x_ = segStart.x_;
        intersection.y_ = scannerM * segStart.x_ + yInt;
    }
    else
    {
        float laserYInt = scannerM * (-scanPt.x_) + scanPt.y_;
        float segmentYInt = segmentM* (-segStart.x_) + segStart.y_;
        intersection.x_ = (segmentYInt - laserYInt)/(scannerM - segmentM);
        intersection.y_ = scannerM * intersection.x_ + laserYInt;
    }
    
    // Run last checks:
    if (scanBackwards(scanPt.x_, scanPt.y_, scanAngle, intersection))
    {
        intersection.x_ = std::numeric_limits<float>::infinity(); 
        intersection.y_ = std::numeric_limits<float>::infinity(); 
        return;
    }
    if (scanOffSegment(intersection, segStart, segEnd))
    {
        intersection.x_ = std::numeric_limits<float>::infinity(); 
        intersection.y_ = std::numeric_limits<float>::infinity(); 
        return;
    }
    return;    
}


bool LaserScanner::scanBackwards(float scannerX, float scannerY, 
                                 float scannerTheta, 
                                 Point& intersection)
{
    // Find angle of intersection point, relative to scanner point.             
    // Translate laser scan line to intersect origin.                           
    // Take that angle with atan2                                               
    float intersectionAngle = atan2( (intersection.y_ - scannerY),                
                                     (intersection.x_ - scannerX));               

    if (!CommonMath::approxEqual(intersectionAngle, 
         CommonMath::tuneAngle(scannerTheta), 3))            
        return true;                                                            
    return false;                                                               
}


bool LaserScanner::scanOffSegment(Point& intersection,        
                                  Point& segStart, Point& segEnd)
{                                                                               
    if ((intersection.x_ < std::min(segStart.x_,segEnd.x_)) ||                              
          (intersection.x_ > std::max(segStart.x_, segEnd.x_)))                             
    {                                                                           
        // handle rounding error cases for narrow ranges of segX1 and segX2     
        if (!(CommonMath::approxEqual(segStart.x_, segEnd.x_, 3) &&    
            CommonMath::approxEqual(segStart.x_, intersection.x_, 3)))
        {                                                                       
            return true;                                                        
        }                                                                       
    }                                                                           
    if ((intersection.y_ < std::min(segStart.y_,segEnd.y_)) ||                              
          (intersection.y_ > std::max(segStart.y_,segEnd.y_)))                              
    {                                                                           
        //std::cout << "Y triggered" << std::endl;                                
        // handle rounding error cases for narrow ranges of segY1 and segY2     
        if (!(CommonMath::approxEqual(segStart.y_, segEnd.y_, 3) &&
            CommonMath::approxEqual(segStart.y_, intersection.y_, 3)))
        {                                                                       
            return true;                                                        
        }                                                                       
    }                                                                           
    return false;                                                               
} 


