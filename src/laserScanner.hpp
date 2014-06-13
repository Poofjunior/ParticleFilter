/**
 * laserScanner.hpp
 * \author Joshua Vasquez
 * \date June 12, 2014
 */

#ifndef LASERSCANNER_HPP 
#define LASERSCANNER_HPP

/**
 * \class LaserScanner 
 * \brief a laser scanner consisting of various measurements over an arc
 *        of defined length 
 */
class LaserScanner {

public:
    LaserScanner(float angleSpread, float numPoints);
    ~LaserScanner();
    // TODO: Disable the default copy constructor.
    static void getIntersection(


private:
    numPoints_;
    angleSpread_;
    stepAngle_;      ///< angle (in radians!) between scan points
    float * scan_;   ///< the laser scanner distances within the range: 
                    ///< (-angleSpread / 2) < scan[i] < (anglesSpread/2) 



};
#endif // LASERSCANNER_HPP 


