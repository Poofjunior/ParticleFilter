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
#include <math.h>
#include "map.hpp"

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

/**
 * \fn float wallDist( float scannerX, float scannerY, float lasTheta, 
                        float segX1, float segY1, float segX2, float segY2); 
 * \brief returns distance from scanner to segment, or -1 otherwise. 
 * \details ray is a single ray from the laser, and segment is from the map
 */ 
    float wallDist( float scannerX, float scannerY, float scannerTheta,
                     float segX1, float segY1, float segX2, float segY2); 


private:
/**
 * \fn template<typename T> bool approxEqual(T approxVal, T actualVal, 
 *                                           float percentError) 
 * \brief return true if both values are equal within percent error.
 * \details percent error is given as a percent.
 */
template<typename T> bool approxEqual(T approxVal, T actualVal,         
                                      float percentError)            
{                                                                               
    return (((std::abs(static_cast<float>(approxVal) 
            - static_cast<float>(actualVal))) / static_cast<float>(actualVal) 
            * 100.0) < percentError);                                           
}   

/**
 * \fn bool scanBackwards(float scannerX, float scannerY, float laserTheta
 *                        float intersectionX, float intersectionY)
 * \brief true if laser scanner line intersects a wall from the wrong direction
 * \details laser scan lines are actually rays. This function alerts us
 *          to false-positive intersections.
 */
    bool scanBackwards(float scannerX, float scannerY, float laserTheta, 
                       float intersectionX, float intersectionY);

/**
 * \fn bool scanOffSegment();
 * \brief true if laser scan line and wall line intersect, but intersection is
 *        outside the bounds of the wall segment
 */
    bool scanOffSegment(float intersectionX, float intersectionY,
                        float segX1, float segY1, float segX2, float segY2);

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


