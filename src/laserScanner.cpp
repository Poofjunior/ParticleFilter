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


LaserScanner::getIntersection( segment & wall)
{


}
