/**
 * commonMath.cpp
 * \author Joshua Vasquez
 * \date June 14, 2014
 */
#include "commonMath.hpp"

//FIXME: change std::numeric_limits<float>::infinity to a constexpr

bool CommonMath::parallel(float slopeA, float slopeB)
{
    // TODO: rounding here is probably redundant at this point.
    // round huge and tiny numbers to inf and zero respectively:
    float roundedA = round(slopeA);
    float roundedB = round(slopeB);

    // Handle special case where parallel vertical lines could round to 
    // opposite slopes.
    if((roundedA == std::numeric_limits<float>::infinity() ||
       (roundedA == -std::numeric_limits<float>::infinity())) &&
       (roundedB == std::numeric_limits<float>::infinity() ||
       (roundedB == -std::numeric_limits<float>::infinity())))
        return true;

    // check if both lines are equal to within 1% 
    if (approxEqual(roundedA, roundedB, 1))
        return true;

    return false;
}

float CommonMath::tuneAngle(float angleInDeg)
{
    float newAngle  = angleInDeg;
    // Map to circle range:
    while (newAngle > 2*M_PI)
        newAngle -= 2*M_PI;    
    while (newAngle < -2*M_PI)
        newAngle += 2*M_PI;    

    // Convert to -Pi to Pi range. FIXME: should this be pi/2 to pi/2 range??
    if (newAngle > M_PI)
        newAngle -= 2*M_PI;
    if (newAngle < -M_PI)
        newAngle += 2*M_PI;

    return newAngle;

}


float CommonMath::round(float input)                                                    
{                                                                               
    if (input > largeVal_)                                                          
        return std::numeric_limits<float>::infinity(); 
    if (input < -largeVal_)                                                          
        return -std::numeric_limits<float>::infinity();                          
    if (std::abs(input) < smallVal_) 
        return 0.;                                                                 
    return input;                                                               
} 


bool CommonMath::approxEqual(float approxVal, float actualVal,
                            float percentError)
{
    // Avoid divide-by-zero.
    if( round(actualVal) == 0.0)                        
    {                                                                       
        return (round(approxVal) == 0.0);               
    }                                                                       
                                                                            
    return (((std::abs(approxVal - actualVal) / std::abs(actualVal)) * 100.0) 
           < percentError);  
}
