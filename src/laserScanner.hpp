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
/** 
 * \fn LaserScanner(float angleSpread = 2.0943951023931953, 
 *                  size_t numPoints = 5);
 * \brief constructs a laser scanner object with specified parameters
 * \details for a single laser dot, choose and angleSpread of 0 and
 * numPoints = 1. Default is 5 numPoints and 2.094395... radians (120 deg).
 */
    //LaserScanner(float angleSpread = 2.0943951023931953, size_t numPoints = 27);
    //LaserScanner(float angleSpread = 0, size_t numPoints = 1);
    LaserScanner(float angleSpread = 2.0943951023931953, size_t numPoints = 3);
    ~LaserScanner();
    // TODO: Disable the default copy constructor.

/**
 * \fn takeScan()
 * \brief update the scan_ values with new scan data
 */
    void takeScan(Pose& pose, Map& map);

/**
 * static float getDist(Point& pt1, Point& pt2)
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
                                 Point& scanPt, 
                                 float scanAngle, Point& segStart,
                                 Point& segEnd);

    static bool scanBackwards(float scannerX, float scannerY,
                       float scannerTheta,
                       Point& intersection);

    static bool scanOffSegment(Point& intersection, Point& segStart, 
                               Point& segEnd);

    static bool scanColinear(Point& scanPt, Point& intersection);

    float * scan_;   ///< the laser scanner distances within the range: 
                    ///< (-angleSpread / 2) < scan[i] < (anglesSpread/2) 
    Point * intersections_;   ///< the laser scanner corresponding
                              ///< intersections with the environment. 
    size_t numPoints_;

private:
    float angleSpread_; ///< angle (in radians!) spanned by min and max beams
    float step_;      ///< angle (in radians!) between scan points
};
#endif // LASERSCANNER_HPP 


