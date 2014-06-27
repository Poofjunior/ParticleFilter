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
    intersections_ = new Point[numPoints];
    step_ = angleSpread / (numPoints - 1);
}


LaserScanner::~LaserScanner()
{
    delete [] scan_;
    delete [] intersections_;
}

void LaserScanner::takeScan(Pose& pose, Map& map)
{
    //std::cout << std::endl;
    float angleToMeasR = (pose.theta_ - (angleSpread_/2));
    Point intersection;
    Point bestIntersection;
    Point scanPt(pose.x_, pose.y_); 
    Point segStart, segEnd;
    float distToSeg;
    float minDistSoFar = std::numeric_limits<float>::infinity();
    std::list<Point>::iterator nextPtIter;

    // For all angles, for all map segs, get closest wall dist. 
    for(size_t beamIndex = 0; beamIndex < numPoints_; ++beamIndex)
    {
        angleToMeasR = CommonMath::tuneAngle(angleToMeasR);
        //std::cout << "angleToMeasR: " << angleToMeasR << std::endl;
        // Find minimum with a best-so-far iteration method.
        minDistSoFar = std::numeric_limits<float>::infinity();
        bestIntersection.x_ = std::numeric_limits<float>::infinity(); 
        bestIntersection.y_ = std::numeric_limits<float>::infinity(); 

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

                    getIntersection(intersection, scanPt, angleToMeasR,  
                                    segStart, segEnd); 
                    

                    distToSeg = getDist(scanPt, intersection);

                    if (distToSeg < minDistSoFar)
                    {
                        minDistSoFar = distToSeg;
                        bestIntersection = intersection;
                    }
                }
            }
        }
/*
        std::cout << "intersection: " << bestIntersection.x_ << ", " 
            << bestIntersection.y_ << std::endl;
*/
        intersections_[beamIndex] = bestIntersection;
        scan_[beamIndex] = minDistSoFar; 
        angleToMeasR += step_;
/*
        std::cout << "minDist:" << minDistSoFar <<  std::endl;
        std::cout << "   bestIntersection: " << bestIntersection.x_  << "," 
                  << bestIntersection.y_ << std::endl;
*/
    }
    
}

float LaserScanner::getDist(Point& pt1, Point& pt2)
{
    return sqrt( (pow( (pt1.x_ - pt2.x_), 2) + 
                  pow( (pt1.y_ - pt2.y_), 2)));
}

void LaserScanner::getIntersection(Point& intersection, 
                                   Point& scanPt, 
                                   float scanAngleR, 
                                   Point& segStart, Point& segEnd)
{
    float scannerM = CommonMath::round(tan(scanAngleR));
    float segmentM = CommonMath::round((segEnd.y_ - segStart.y_)
                                      /(segEnd.x_ - segStart.x_));
    
    if (CommonMath::parallel(scannerM, segmentM))
    {
        //std::cout << "PARALELL" << std::endl;
        intersection.x_ = std::numeric_limits<float>::infinity(); 
        intersection.y_ = std::numeric_limits<float>::infinity(); 
        return;
    }

    /// Check if scan is basically on the wall:
    //FIXME: laser intersection is unassigned at this point! Check later or
    // make segStart, segEnd inputs to this function!!!
    if (scanColinear(intersection, scanPt))
    {
        //std::cout << "scanColinear!" << std::endl;
        intersection.x_ = scanPt.x_;
        intersection.y_ = scanPt.y_; 
        return;
    }
    
    float yInt;
    if (std::abs(scannerM) == std::numeric_limits<float>::infinity()) 
    {
        //std::cout << "laserVertical" << std::endl;
        yInt = segmentM * (-segStart.x_) + segStart.y_;
        intersection.x_ = scanPt.x_;
        intersection.y_ = segmentM * scanPt.x_ + yInt;
    }
    else if (std::abs(segmentM) == std::numeric_limits<float>::infinity()) 
    {
        //std::cout << "WallVertical" << std::endl;
        yInt = scannerM * (-scanPt.x_) + scanPt.y_;
        intersection.x_ = segStart.x_;
        intersection.y_ = scannerM * segStart.x_ + yInt;
    }
    else
    {
        //std::cout << "NORMAL INTERCEPT" << std::endl;
        float laserYInt = scannerM * (-scanPt.x_) + scanPt.y_;
        float segmentYInt = segmentM* (-segStart.x_) + segStart.y_;


        intersection.x_ = CommonMath::round((segmentYInt - laserYInt)
                                           /(scannerM - segmentM));
        intersection.y_ = CommonMath::round(scannerM * intersection.x_ 
                                            + laserYInt);
    }
/*
        std::cout << "scannerM: " << scannerM << std::endl;
        std::cout << "segmentM: " << segmentM << std::endl;
        //std::cout << "laserYInt: " << laserYInt << std::endl;
        //std::cout << "segmentYInt: " << segmentYInt << std::endl;
        std::cout << "intersection: (" << intersection.x_ << ", " 
                  << intersection.y_ << ")" << std::endl;
*/
    
    // Run last checks:
    if (scanOffSegment(intersection, segStart, segEnd))
    {
        //std::cout << "SCAN OFF SEGMENT" << std::endl;
        intersection.x_ = std::numeric_limits<float>::infinity(); 
        intersection.y_ = std::numeric_limits<float>::infinity(); 
        return;
    }
    /// scanOffSegment must be checked first so that intersection isnt inf!
    if (scanBackwards(scanPt.x_, scanPt.y_, scanAngleR, intersection))
    {
        //std::cout << "SCAN BACKWARDS" << std::endl;
        //std::cout << "scannerM: " << scannerM << std::endl;
        //std::cout << "segmentM: " << segmentM << std::endl;
        intersection.x_ = std::numeric_limits<float>::infinity(); 
        intersection.y_ = std::numeric_limits<float>::infinity(); 
        return;
    }
    return;    
}


bool LaserScanner::scanBackwards(float scannerX, float scannerY, 
                                 float scannerThetaR, 
                                 Point& intersection)
{
    // Find angle of intersection point, relative to scanner point.             
    // Translate laser scan line to intersect origin.                           
    // Take that angle with atan2                                               
    

    float intersectionAngle = atan2( (intersection.y_ - scannerY),                
                                     (intersection.x_ - scannerX));               

/*
    std::cout << "scanBackwardsDEBUG: intersectAngle (inrad):" 
              << intersectionAngle << ", scannerThetaR (in rad): "
              << scannerThetaR
              << std::endl;
*/

    if (!CommonMath::almostEqual(intersectionAngle, 
         scannerThetaR, CommonMath::ulp_))            
        return true;                                                            

    return false;                                                               
}


bool LaserScanner::scanOffSegment(Point& intersection,        
                                  Point& segStart, Point& segEnd)
{                                                                               
    // Throw out intersections at infinity:
    if (std::abs(intersection.x_) == std::numeric_limits<float>::infinity())
        return true; 
    if (std::abs(intersection.y_) == std::numeric_limits<float>::infinity())
        return true; 

    // Check if range exceeded in x:
    if ((intersection.x_ < std::min(segStart.x_,segEnd.x_)) || 
          (intersection.x_ > std::max(segStart.x_, segEnd.x_)))
    {                                                                           
        // handle rounding error cases for narrow ranges of segX1 and segX2     
        if (!(CommonMath::almostEqual(segStart.x_, segEnd.x_, CommonMath::ulp_)
            && CommonMath::almostEqual(segStart.x_, intersection.x_, 
                                       CommonMath::ulp_)))
        {                                                                       
            return true;                                                        
        }                                                                       
    }                                                                           
    // Check if range exceeded in y:
    if ((intersection.y_ < std::min(segStart.y_,segEnd.y_)) ||
          (intersection.y_ > std::max(segStart.y_,segEnd.y_))) 
    {                                                                           
        // handle rounding error cases for narrow ranges of segY1 and segY2     
        if (!(CommonMath::almostEqual(segStart.y_, segEnd.y_, CommonMath::ulp_)
            && CommonMath::almostEqual(segStart.y_, intersection.y_, 
                                       CommonMath::ulp_)))
        {                                                                       
            return true;                                                        
        }                                                                       
    }                                                                           
    return false;                                                               
} 

bool LaserScanner::scanColinear(Point& scanPt, Point& intersection) 
{
    if (CommonMath::almostEqual(intersection.x_, scanPt.x_, CommonMath::ulp_) 
        && 
        CommonMath::almostEqual(intersection.y_, scanPt.y_, CommonMath::ulp_) )
        return true;
    return false;
}
