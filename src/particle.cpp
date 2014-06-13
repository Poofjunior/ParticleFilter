/**
 * particle.cpp
 * \author Joshua Vasquez
 * \date May 1, 2014 to June 12, 2014
 */
#include "particle.hpp"

// Particle Member functions
Particle::Particle(float x, float y, float theta, float weight)
:pose_.x_{x}, pose_.y_{y}, pose_.theta_{theta}, pose_.weight_{weight}
{
    // Nothing else to do!
}


Particles::Particle::~Particle()
{
    // Nothing to do!
}


void Particle::propagate()
{
    MotionModel_.updatePose(pose_);    
}


