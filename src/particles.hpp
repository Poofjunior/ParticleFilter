/**
 * particles.hpp
 * \author Joshua Vasquez
 * \date April 30, 2014 to June 12, 2014
 */

#ifndef PARTICLES_HPP
#define PARTICLES_HPP
#include <random>
#include <iostream>
#include <limits>
#include <ctgmath>
#include <math.h>
#include "map.hpp"
#include "particle.hpp"
#include "motionModel.hpp"

class Particles {
public:
    Particles(size_t numParticles);
    ~Particles();

    size_t numParticles_;
    Particle** theParticles_;   ///< a list of pointers to particles
    Particle bestPart_;         ///< the average of all particle poses

///TODO: initParticles should have an xmin and ymin too.
/**
 * \fn initParticles(float xmax, float ymax)
 * \brief Generate random poses and assign them to particles.
 * \details Poses are generated from a uniform distribution.
 */
    void initParticles(float xmax, float ymax);

/**
 * \fn takeScan(Map& map)
 * \brief have all particles take a scan from their pose on the map.
 */
    void takeScan(Map& map);

/**
 * \fn propagateParticles()
 * \brief Move each particle to new pose given the current odometry
 *        data.
 * \details A small amount of random noise is added to the movement
 *          of each particle.
 */
    void propagateParticles();

/**
 * \fn void computeBestParticle()
 * \brief computes the average pose of all particles
 */
    void computeBestParticle();
};
#endif // PARTICLES_HPP


