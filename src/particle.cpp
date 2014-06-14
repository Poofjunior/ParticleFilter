/**
 * particle.cpp
 * \author Joshua Vasquez
 * \date May 1, 2014 to June 12, 2014
 */
#include "particle.hpp"

// Particle Member functions
Particle::Particle(float x, float y, float theta, float weight)
:pose_(x, y, theta), weight_(weight)
{
    // Nothing else to do!
}


Particle::~Particle()
{
    // Nothing to do!
}


void Particle::propagate()
{
    MotionModel::updatePose(pose_);    
}


