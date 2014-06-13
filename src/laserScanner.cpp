/**
 * laserScanner.hpp
 * \author Joshua Vasquez
 * \date June 12, 2014
 */

#include "laserScanner.hpp"

LaserScanner::LaserScanner(float angleSpread, numPoints)
:angleSpread_{angleSpread}, numPoints_{numPoints}
{
    // Create the array for scan distances:
    scan_ = new int*[numPoints];

}


LaserScanner::~LaserScanner()
{
    delete [] scan_;
}


void LaserScanner::getIntersection(Point& intersection, 
                                   float scannerX, float scannerY, 
                                   float scanAngle, 
                                   Point& segStart, Point& segEnd;
{
    float scannerM = round(tan(tuneAngle(scanAngle)));
    float segmentM = (segEnd.y_ - segStart.y_)/(segEnd.x_ - segStart.x_);
    
    // copy from particlesOld.cpp in the non-repo version.
}
