/**
 * particles.hpp
 * \author Joshua Vasquez
 * \date June 12, 2014
 */

#ifndef PARTICLE_HPP
#define PARTICLE_HPP
#include "pose.hpp"
#include "laserScanner.hpp"
#include "motionModel.hpp"

class Particle {
public:
    Particle(float x = 0, float y = 0, float theta = 0, float weight_ = 0);
    ~Particle();
/**
 * \fn void propagate();
 * \brief update particle pose according to robot-specific motion model.
 */    
        void propagate(bool noise = false);
    
        Pose pose_;
        LaserScanner laser_;
        double weight_;
};
#endif // PARTICLE_HPP


