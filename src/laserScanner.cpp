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

//TODO: should this be static?
static void LaserScanner::getIntersection(Point& intersection, 
                                   float scannerX, float scannerY, 
                                   float scanAngle, 
                                   Point& segStart, Point& segEnd)
{
    float scannerM = round(tan(tuneAngle(scanAngle)));
    float segmentM = (segEnd.y_ - segStart.y_)/(segEnd.x_ - segStart.x_);
    
    // TODO: finish writing this.
    // copy from particlesOld.cpp in the non-repo version.
}


bool LaserScanner::scanBackwards(float scannerX, float scannerY, 
                                 float scannerTheta, 
                                 float intersectionX, float intersectionY)
{
//TODO: change input args to Points
    // Find angle of intersection point, relative to scanner point.             
    // Translate laser scan line to intersect origin.                           
    // Take that angle with atan2                                               
    float intersectionAngle = atan2( (intersectionY - scannerY),                
                                     (intersectionX - scannerX));               
/*                                                                              
    std::cout << "intersectionAngle: " << intersectionAngle << std::endl;       
    std::cout << "laser angle: " << tuneAngle(scannerTheta) << std::endl;       
*/                                                                              
    if (!approxEqual(intersectionAngle, tuneAngle(scannerTheta), 3))            
    {                                                                           
        return true;                                                            
    }                                                                           
    return false;                                                               
}


bool Particles::scanOffSegment(float intersectionX, float intersectionY,        
                           float segX1, float segY1, float segX2, float segY2)
{                                                                               
    if ((intersectionX < std::min(segX1,segX2)) ||                              
          (intersectionX > std::max(segX1, segX2)))                             
    {                                                                           
        // handle rounding error cases for narrow ranges of segX1 and segX2     
        if (!(approxEqual(segX1, segX2, 3) &&                                   
            approxEqual(segX1, intersectionX, 3)))                              
        {                                                                       
            return true;                                                        
        }                                                                       
    }                                                                           
    if ((intersectionY < std::min(segY1,segY2)) ||                              
          (intersectionY > std::max(segY1,segY2)))                              
    {                                                                           
        std::cout << "Y triggered" << std::endl;                                
        // handle rounding error cases for narrow ranges of segY1 and segY2     
        if (!(approxEqual(segY1, segY2, 3) &&                                   
            approxEqual(segY1, intersectionY, 3)))                              
        {                                                                       
            return true;                                                        
        }                                                                       
    }                                                                           
    return false;                                                               
} 


