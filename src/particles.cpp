/**
 * particles.cpp
 * \author Joshua Vasquez
 * \date May 1, 2014 to June 12, 2014
 */
#include "particles.hpp"

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

void Particles::initParticles(float xmax, float ymax)
{
    std::default_random_engine generator;
    //FIXME: change to real distributions, not int distributions.
    std::uniform_int_distribution<int> distributionX(0,xmax);
    std::uniform_int_distribution<int> distributionY(0,ymax);
    std::uniform_int_distribution<int> distributionTheta(0,360);

    for(size_t eachPart = 0; eachPart < numParticles_; ++eachPart)
    {
        theParticles_[eachPart]->pose_.x_ = distributionX(generator);
        theParticles_[eachPart]->pose.y_ = distributionY(generator);
        theParticles_[eachPart]->pose.theta_ = distributionTheta(generator);
    }

}

void Particles::takeScan()
{
    for(size_t eachPart = 0; eachPart < numParticles_; ++eachPart)
    {
        theParticles[eachPart].laser_.takeScan();
    }

}

void Particles::propagateParticles()
{

}
