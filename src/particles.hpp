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

class Particles {
public:
    Particles(size_t numParticles);
    ~Particles();

    size_t numParticles_;
    Particle** theParticles_;   ///< a list of pointers to particles

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
    // FIXME: is passing in the map the best way to do this?
    void takeScan(Map& map);

/**
 * \fn propagateParticles()
 * \brief Move each particle to new pose given the current odometry
 *        data.
 * \details A small amount of random noise is added to the movement
 *          of each particle.
 */
    void propagateParticles();
};
#endif // PARTICLES_HPP


