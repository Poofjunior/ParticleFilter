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

/**
 * \fn parallel(float slopeA, slopeB)
 * \brief true if both lines are parallel within rounding error
 * \details handles special case of slopeA: +inf and slopeB: -inf
 */
bool parallel( float slopeA, float slopeB);

/**
 * \fn round(float input)
 * \brief rounds input to infinities or to zero for extreme values to prevent
 *        rounding error
 */
bool round(float input);


bool approxEqual( float val1, float val2, float percentError);

bool tuneAngle(float angle);
};

#endif // COMMONMATH_HPP
