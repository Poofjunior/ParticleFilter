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
#include "pose.hpp"
#include "commonMath.hpp"
#include "map.hpp"

/**
 * \class LaserScanner 
 * \brief a laser scanner consisting of various measurements over an arc
 *        of defined length 
 */
class LaserScanner {

public:
    LaserScanner(float angleSpread = 120, size_t numPoints = 5);
    ~LaserScanner();
    // TODO: Disable the default copy constructor.

/**
 * \fn takeScan()
 * \brief update the scan_ values with new scan data
 */
    static void takeScan(Pose& pose, Map& map);

/**
 * float getDist(Point& pt1, Point& pt2)
 * \brief return the distance between two points
 */
    static float getDist(Point& pt1, Point& pt2);

/**
 * static void getIntersection( Point& intersection,
 *                              Point& scanPt, 
 *                              float scanAngle, Point& segStart,
 *                              Point& segEnd);
 * \brief find the intersection point of the line segment from the given
 *        scanner location 
 */
    static void getIntersection( Point& intersection, 
                                 float scannerX, float scannerY, 
                                 float scanAngle, Point& segStart,
                                 Point& segEnd);

    static bool scanBackwards(float scannerX, float scannerY,
                       float scannerTheta,
                       Point& intersection);

    static bool scanOffSegment(Point& intersection, Point& segStart, 
                               Point& segEnd);


private:
    float angleSpread_;
    size_t numPoints_;
    float step_;      ///< angle (in radians!) between scan points
    float * scan_;   ///< the laser scanner distances within the range: 
                    ///< (-angleSpread / 2) < scan[i] < (anglesSpread/2) 
};
#endif // LASERSCANNER_HPP 


