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
    /// Disable copy constructor and assignment operator.
    /// Note: Particles are regenerated later, but copies don't carry over
    ///     the weight_ data member, so a copy is done manually part by part to
    ///     be explicit.
    Particle(const Particle& otherParticle) = delete;
    Particle& operator=(const Particle& otherParticle) = delete;
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


