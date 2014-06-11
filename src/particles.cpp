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
    float laserM = tan(scannerTheta * M_PI / 180.0);
    float segmentM = (segY2 - segY1)/(segX2 - segX1); 

    // FIXME: test approxEqual on both arguments infinity.
    if (approxEqual(laserM, segmentM, 1))
        return std::numeric_limits<float>::infinity();

    // Use geometry for vertical lines.
    if(segmentM == std::numeric_limits<float>::infinity())
    {
        return std::abs(segX1 - scannerX) / cos(scannerTheta);
    }
    if(laserM == std::numeric_limits<float>::infinity())
    {
        // FIXME verify that this works in all cases
        float wallAngle = atan2((segY2 - segY1), (segX2 - segX1));
        return std::abs(segX1 - scannerX) / cos(wallAngle);
    }
    // Use algebra for all other cases.
    float laserYInt = laserM*(-scannerX) + scannerY;
    float segmentYInt = segmentM * (-segX1) + segY1;
    float intersectionX = (segmentYInt - laserYInt)/(laserM - segmentM);
    float intersectionY = laserM*intersectionX + laserYInt;
    
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


bool Particles::scanBackwards(float scannerX, float scannerY, float laserTheta,        
                              float intersectionX, float intersectionY)
{
    // Find angle of intersection point, relative to scanner point.
    // Translate laser scan line to intersect origin.
    // Take that angle with atan2
    float intersectionAngle = atan2( (intersectionY - scannerY),
                                     (intersectionX - scannerX));
    
    return (approxEqual(intersectionAngle, laserTheta, 3));
}


bool Particles::scanOffSegment(float intersectionX, float intersectionY,               
                           float segX1, float segY1, float segX2, float segY2)
{
    if (!(intersectionX > std::min(segX1,segX2) && 
          intersectionX < std::max(segX1, segX2)))
        return false;
    if (!(intersectionY > std::min(segY1,segY2) && 
          intersectionY < std::max(segY1,segY2)))
        return false;
    return true;
}
