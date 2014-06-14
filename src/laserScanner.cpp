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
    scan_ = new float[numPoints_];

}


LaserScanner::~LaserScanner()
{
    delete [] scan_;
}

void LaserScanner::takeScan()
{
    // For all points, calculate their distances and update scan_
}

//TODO: should this be static?
void LaserScanner::getIntersection(Point& intersection, 
                                   float scannerX, float scannerY, 
                                   float scanAngle, 
                                   Point& segStart, Point& segEnd)
{
    float scannerM = round(tan(CommonMath::tuneAngle(scanAngle)));
    float segmentM = (segEnd.y_ - segStart.y_)/(segEnd.x_ - segStart.x_);
    
    // TODO: finish writing this.
    // copy from particlesOld.cpp in the non-repo version.
}


bool LaserScanner::scanBackwards(float scannerX, float scannerY, 
                                 float scannerTheta, 
                                 Point& intersection)
{
//TODO: change input args to Points
    // Find angle of intersection point, relative to scanner point.             
    // Translate laser scan line to intersect origin.                           
    // Take that angle with atan2                                               
    float intersectionAngle = atan2( (intersection.y_ - scannerY),                
                                     (intersection.x_ - scannerX));               
/*                                                                              
    std::cout << "intersectionAngle: " << intersectionAngle << std::endl;       
    std::cout << "laser angle: " << tuneAngle(scannerTheta) << std::endl;       
*/                                                                              
    if (!CommonMath::approxEqual(intersectionAngle, 
         CommonMath::tuneAngle(scannerTheta), 3))            
    {                                                                           
        return true;                                                            
    }                                                                           
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
        std::cout << "Y triggered" << std::endl;                                
        // handle rounding error cases for narrow ranges of segY1 and segY2     
        if (!(CommonMath::approxEqual(segStart.y_, segEnd.y_, 3) &&
            CommonMath::approxEqual(segStart.y_, intersection.y_, 3)))
        {                                                                       
            return true;                                                        
        }                                                                       
    }                                                                           
    return false;                                                               
} 


