/**
 * laserScanner.hpp
 * \author Joshua Vasquez
 * \date June 12, 2014
 */

#ifndef LASERSCANNER_HPP 
#define LASERSCANNER_HPP
#include <cstddef>
#include <iostream>
#include <algorithm>
#include "point.hpp"
#include "commonMath.hpp"

/**
 * \class LaserScanner 
 * \brief a laser scanner consisting of various measurements over an arc
 *        of defined length 
 */
class LaserScanner {

public:
    LaserScanner(float angleSpread = 120, size_t numPoints = 60);
    ~LaserScanner();
    // TODO: Disable the default copy constructor.

/**
 * \fn takeScan()
 * \brief update the scan_ values with new scan data
 */
    void takeScan();

/**
 * static void getIntersection( Point& intersection,
 *                              float scannerX, float scannerY,
 *                              float scanAngle, Point& segStart,
 *                              Point& segEnd);
 * \brief find the intersection point of the line segment from the given
 *        scanner location 
 */
    static void getIntersection( Point& intersection, 
                                 float scannerX, float scannerY, 
                                 float scanAngle, Point& segStart,
                                 Point& segEnd);


private:
    float angleSpread_;
    size_t numPoints_;
    float stepAngle_;      ///< angle (in radians!) between scan points
    float * scan_;   ///< the laser scanner distances within the range: 
                    ///< (-angleSpread / 2) < scan[i] < (anglesSpread/2) 
    
    bool scanBackwards(float scannerX, float scannerY,
                       float scannerTheta,
                       Point& intersection);

    bool scanOffSegment(Point& intersection, Point& segStart, Point& segEnd);



};
#endif // LASERSCANNER_HPP 


