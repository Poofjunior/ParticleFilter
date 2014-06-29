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
    std::default_random_engine generator((unsigned int)time(0));

    std::uniform_real_distribution<float> distributionX(0,xmax);
    std::uniform_real_distribution<float> distributionY(0,ymax);
    std::uniform_real_distribution<float> distributionTheta(-M_PI, M_PI);

    for(size_t eachPart = 0; eachPart < numParticles_; ++eachPart)
    {
        theParticles_[eachPart]->pose_.x_ = distributionX(generator);
        theParticles_[eachPart]->pose_.y_ = distributionY(generator);
        theParticles_[eachPart]->pose_.theta_ = distributionTheta(generator);
    }

}

void Particles::takeScan(Map& map)
{
    for(size_t eachPart = 0; eachPart < numParticles_; ++eachPart)
    {
        theParticles_[eachPart]->laser_.takeScan(
                                            theParticles_[eachPart]->pose_,
                                            map);
    }

}

void Particles::propagateParticles()
{
    for(size_t eachPart = 0; eachPart < numParticles_; ++eachPart)
    {
        theParticles_[eachPart]->propagate();
    }

}

void Particles::scoreParticles(LaserScanner& laser)
{
    /// Assume the same number of laser beam points for all particles:
    int numLaserPts = theParticles_[0]->laser_.numPoints_;


    /// Compute each particle's compound probability of numLaserPts
    // independent  laser beam events.
    for(size_t eachPart = 0; eachPart < numParticles_; ++eachPart)
    {
        theParticles_[eachPart]->weight_ = 1.0; 
        /// Compute probability density function for each beam
        for (size_t beamIter = 0; beamIter < numLaserPts; ++beamIter)
        {
        theParticles_[eachPart]->weight_ *=  
            CommonMath::pdf(
                   theParticles_[eachPart]->laser_.scan_[beamIter],
                   laser.scan_[beamIter], sigma_); 
        }
        std::cout << "weight: " << theParticles_[eachPart]->weight_ 
                  << std::endl;
        std::cout << std::endl;
    }

}

void Particles::computeBestParticle()
{
    for (size_t eachPart = 0; eachPart < numParticles_; ++eachPart)
    {
        bestPart_.pose_.x_ += theParticles_[eachPart]->pose_.x_; 
        bestPart_.pose_.y_ += theParticles_[eachPart]->pose_.y_; 
        bestPart_.pose_.theta_ += theParticles_[eachPart]->pose_.theta_; 
    }
        bestPart_.pose_.x_ /= numParticles_;
        bestPart_.pose_.y_ /= numParticles_;
        bestPart_.pose_.theta_ /= numParticles_;
}
