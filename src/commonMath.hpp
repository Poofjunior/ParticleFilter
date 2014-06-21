/** 
 * commonMath.hpp
 * \author Joshua Vasquez
 * \date June 12, 2014
 */

#ifndef COMMONMATH_HPP
#define COMMONMATH_HPP
#include <limits>
#include <ctgmath>
namespace CommonMath {

const float largeVal_ = 1000; 
const float smallVal_ = 0.001;

/**
 * \fn parallel(float slopeA, slopeB)
 * \brief true if both lines are parallel within rounding error
 * \details handles special case of slopeA: +inf and slopeB: -inf
 */
bool parallel( float slopeA, float slopeB);

/**
 * \fn float round(float input)
 * \brief rounds input to infinities or to zero for extreme values to prevent
 *        rounding error
 */
float round(float input);


bool approxEqual( float val1, float val2, float percentError);
/**
 * \fn tuneAngle(float angle)
 * \brief converts input float (in radians) to the correct range of -Pi to Pi.
 */
float tuneAngle(float angle);
};

#endif // COMMONMATH_HPP
