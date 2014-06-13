/**
 * commonMath.cpp
 * \author Joshua Vasquez
 * \date June 14, 2014
 */
#include "commonMath.hpp"

bool CommonMath::parallel(float slopeA, float slopeB)
{
    // round huge and tiny numbers to inf and zero respectively:
    float roundedA = round(slopeA);
    float roundedB = round(slopeB);

    // Handle special case where parallel vertical lines could round to 
    // opposite slopes.
    if((roundedA == std::numeric_limits<float>::infinity() ||
       (rounded A == -std::numeric_limits<float>::infinity())) &&
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
    while (newAngle > 360)
        newAngle -= 360;    
    while (newAngle < -360)
        newAngle += 360;    

    // Convert to -Pi/2 to Pi/2 range.
    if (newAngle > 180.)
        newAngle -= 360.;
    if (newAngle < -180.)
        newAngle += 360.;

    // Convert to radian.
    newAngle *= (M_PI/180.);
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
    if( round(actualVal) == 0.0)                        
    {                                                                       
        return (round(approxVal) == 0.0);               
    }                                                                       
                                                                            
    return (((std::abs(approxVal - actualVal) / std::abs(actualVal)) * 100.0) 
           < percentError);  
}


bool Particles::scanBackwards(float scannerX, float scannerY, 
                              float scannerTheta,        
                              float intersectionX, float intersectionY)
{
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
