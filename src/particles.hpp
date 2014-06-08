/**
 * particles.hpp
 * \author Joshua Vasquez
 * \date April 30, 2014
 */

#ifndef PARTICLES_HPP
#define PARTICLES_HPP
#include <random>
#include <iostream>
#include <ctgmath>

class Particles {
public:
/**
 * \class Particle 
 * \brief a generic container for robot pose
 */
    class Particle {
    public:
        Particle(double xVal, double yVal, double weight);
        ~Particle();
/**
 * \fn virtual void updateParticle();
 * \brief update particle pose according to robot-specific motion model.
 * \details a little gaussian noise is thrown into the motion of each wheel.
 */    
        void updateParticle(double lWheelDelta, double rWheelDelta, 
                            bool noise = 0);
    
    // FIXME: figure out what should be public and private!
    // FIXME: should these be private and make Particles a friend class?
        double xVal_;
        double yVal_;
        double theta_;
        double weight_;
    };

    Particles(size_t numParticles);
    ~Particles();
    size_t numParticles_;
    Particle** theParticles_;   ///< a list of pointers to particles

/**
 * \fn scatterParticles(float xmax, float ymax)
 * \brief Generate random poses and assign them to particles.
 * \details Poses are generated from a uniform distribution.
 */
    void scatterParticles(float xmax, float ymax);

/**
 * \fn propagateParticles()
 * \brief Move each particle to new pose given the current odometry
 *        data.
 * \details A small amount of random noise is added to the movement
 *          of each particle.
 */
    void propagateParticles();

/**
 * \fn void updateParticles();
 * \brief uh.. do I need a function that does this?
 */
    void updateParticles();


private:
/**
 * \class robotParams 
 * \brief a generic container for robot pose
 * \details units are in meters
 */
    class robotParams{
    public:
    private:
        friend class Particle;
        static const double wheelRadius_;
        static const double wheelSpacing_;
    };

};
#endif // PARTICLES_HPP


