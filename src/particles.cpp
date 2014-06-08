/**
 * particles.cpp
 * \author Joshua Vasquez
 * \date May 1, 2014
 */
#include "particles.hpp"

// Constants. Alas, C++ wont let me put these in the header file since theyre
// doubles.
double const Particles::robotParams::wheelRadius_ = 0.1;
double const Particles::robotParams::wheelSpacing_ = 0.1;

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
    //FIXME: do we need to also delete theParticles_ ???
}

void Particles::scatterParticles(float xmax, float ymax)
{
    std::default_random_engine generator;
    //FIXME: change to real distributions, not int distributions.
    std::uniform_int_distribution<int> distributionX(0,xmax);
    std::uniform_int_distribution<int> distributionY(0,ymax);
    std::uniform_int_distribution<int> distributionTheta(0,360);

    for(int eachPart = 0; eachPart < numParticles_; ++eachPart)
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

