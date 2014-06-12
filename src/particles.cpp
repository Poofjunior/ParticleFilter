/**
 * particles.cpp
 * \author Joshua Vasquez
 * \date May 1, 2014 to June 8, 2014
 */
#include "particles.hpp"
#include <limits>   ///< for representation of inifinity as a float


Particles::Particles(size_t numParticles)
:numParticles_{numParticles}
{
    // dynamically allocate an array of pointers to particles.
    theParticles_ = new Particle*[numParticles_];
    for (size_t eachPart = 0; eachPart < numParticles_; ++eachPart)
        theParticles_[eachPart] = new Particle{0,0,0};
}

Particles::~Particles()
{
    // Free our dynamically allocated memory.
    for (size_t eachPart = 0; eachPart< numParticles_; ++eachPart)
        delete theParticles_[eachPart];
    delete [] theParticles_;    // FIXME: is this a double-delete?
}

void Particles::scatterParticles(float xmax, float ymax)
{
    std::default_random_engine generator;
    //FIXME: change to real distributions, not int distributions.
    std::uniform_int_distribution<int> distributionX(0,xmax);
    std::uniform_int_distribution<int> distributionY(0,ymax);
    std::uniform_int_distribution<int> distributionTheta(0,360);

    for(size_t eachPart = 0; eachPart < numParticles_; ++eachPart)
    {
        theParticles_[eachPart]->xVal_ = distributionX(generator);
        theParticles_[eachPart]->yVal_ = distributionY(generator);
        theParticles_[eachPart]->theta_ = distributionTheta(generator);
    }

}

void Particles::propagateParticles()
{

}

void Particles::updateParticles()
{
}


// Particle Member functions
Particles::Particle::Particle(double xVal, double yVal, double weight)
:xVal_{xVal}, yVal_{yVal}, weight_{weight}
{
    // Nothing else to do!
}


Particles::Particle::~Particle()
{
    // Nothing to do!
}


void Particles::Particle::updateParticle(double lWheelDelta, 
                                        double rWheelDelta, 
                                        bool noise)
{
    double noiseLeftW = 0;
    double noiseRightW = 0;
    
    if (noise)
    {
        // TODO: create the generator once, not each time fn is called!
        std::default_random_engine generator;
        std::normal_distribution<double> distribution(-1.0, 1.0);
        // TODO: tweak noise function later!
        noiseLeftW = (lWheelDelta)*distribution(generator);
        noiseRightW = (rWheelDelta)*distribution(generator);
    } 
    else 
    {
        // Calc new x,y,theta through motion model. Check THETA usage.
        xVal_ += (robotParams::wheelRadius_ / 2) * (lWheelDelta + noiseLeftW + 
                  rWheelDelta + noiseRightW) * cos(theta_*(M_PI/180));
        yVal_ += (robotParams::wheelRadius_ / 2) * (lWheelDelta + noiseLeftW +
                  rWheelDelta + noiseRightW) * sin(theta_*(M_PI/180));
        theta_ += (robotParams::wheelRadius_ / robotParams::wheelSpacing_) * 
                  ((rWheelDelta + noiseRightW)- (lWheelDelta + noiseLeftW));
    }

}


float Particles::getWallDist( float scannerX, float scannerY, float scannerTheta,
                            float segX1, float segY1, float segX2, float segY2)
{

    // Compare Slopes:
    float laserM = round(tan(tuneAngle(scannerTheta)));
    float segmentM = (segY2 - segY1)/(segX2 - segX1); 
    float intersectionX, intersectionY;

    // Handle the case where angles point in opposite vertical directions.
    if((laserM == std::numeric_limits<float>::infinity() ||
       (laserM == -std::numeric_limits<float>::infinity())) &&
       (segmentM == std::numeric_limits<float>::infinity() ||
       (segmentM == -std::numeric_limits<float>::infinity())))
        return std::numeric_limits<float>::infinity();

    // Handle the case where both lines are basically parallel. 
    if (approxEqual(laserM, segmentM, 1))
        return std::numeric_limits<float>::infinity();

    // Use geometry when a vertical line is involved.
    // Old triangle formula: R = x/cos(theta).
    if(segmentM == std::numeric_limits<float>::infinity())
    {
        // FIXME: double-check if off-segment check works
        // FIXME: intersectionDist should be positive!!
        float intersectionDist = std::abs((std::max(segX1,scannerX) - 
                                 std::min(segX1, scannerX))/
                                 cos(tuneAngle(scannerTheta)));
/*
        std::cout <<"intersectionDist:" <<  intersectionDist << std::endl;
*/
        intersectionX = round(scannerX + 
                        intersectionDist * 
                        std::abs(cos(tuneAngle(scannerTheta))));
        intersectionY = round(scannerY + 
                        intersectionDist *
                        std::abs(sin(tuneAngle(scannerTheta))));
/*
        std::cout << "intersection: (" << intersectionX << ", " 
                  << intersectionY << ")" << std::endl;
*/

        // Calculate if intersection is on wall segment.
        if (scanOffSegment(intersectionX, intersectionY, 
                            segX1, segY1, segX2, segY2))
        {
/*
            std::cout << "scan off segment" << std::endl;
*/
            return std::numeric_limits<float>::infinity();
        }

        if (scanBackwards(scannerX, scannerY, scannerTheta, intersectionX,
                          intersectionY)) 
        {
/*
            std::cout << "scan backwards!" << std::endl;
*/
            return std::numeric_limits<float>::infinity();
        }

        return intersectionDist;
    }
    if(laserM == std::numeric_limits<float>::infinity())
    {
        // FIXME: double-check if off-segment check works
        float wallAngle = atan2((segY2 - segY1), (segX2 - segX1));
        float intersectionDist = std::abs((std::max(segX1,scannerX) - 
                                 std::min(segX1, scannerX))/ 
                                 cos(wallAngle));
        intersectionX = round(scannerX + 
                        intersectionDist * 
                        std::abs(cos(tuneAngle(scannerTheta))));
        intersectionY = round(scannerY + 
                        intersectionDist * 
                        std::abs(sin(tuneAngle(scannerTheta))));
        if (scanOffSegment(intersectionX, intersectionY,
                    segX1, segY1, segX2, segY2))
            return std::numeric_limits<float>::infinity();

        if (scanBackwards(scannerX, scannerY, scannerTheta, intersectionX,
                          intersectionY)) 
            return std::numeric_limits<float>::infinity();
        
        else
            return intersectionDist;
    }
    // Use algebra for all other cases.
    float laserYInt = laserM*(-scannerX) + scannerY;
    float segmentYInt = segmentM * (-segX1) + segY1;
    intersectionX = (segmentYInt - laserYInt)/(laserM - segmentM);
    intersectionY = laserM*intersectionX + laserYInt;
    
    if (scanBackwards(scannerX, scannerY, scannerTheta, intersectionX,
                      intersectionY))
        return std::numeric_limits<float>::infinity();

    if (scanOffSegment(intersectionX, intersectionY, segX1, segY1, segX2, 
                       segY2))
        return std::numeric_limits<float>::infinity();

    // translate to origin, and compute distance.
    return sqrt(pow((scannerX - intersectionX), 2) + 
                pow((scannerY - intersectionY), 2));
}


float Particles::tuneAngle(float angleInDeg)
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


float Particles::round(float input)                                                    
{                                                                               
    if (input > largeVal_)                                                          
        return std::numeric_limits<float>::infinity();                          
    if (input < -largeVal_)                                                          
        return -std::numeric_limits<float>::infinity();                          
    if (std::abs(input) < smallVal_) 
        return 0.;                                                                 
    return input;                                                               
} 

bool Particles::approxEqual(float approxVal, float actualVal,
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
        // handle rounding error cases for narrow ranges of segY1 and segY2
        if (!(approxEqual(segY1, segY2, 3) && 
            approxEqual(segY1, intersectionY, 3)))
        {
            return true;
        }
    }
    return false;
}
