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
    for (size_t eachPart = 0; eachPart < numParticles_; ++eachPart)
        delete theParticles_[eachPart];
    delete[] theParticles_;
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
        // Propagate with noise.
        theParticles_[eachPart]->propagate(true);
    }

}

void Particles::scoreParticles(LaserScanner& laser)
{
    totalWeight_ = 0;
    /// Assume the same number of laser beam points for all particles:
    size_t numLaserPts = theParticles_[0]->laser_.numPoints_;

    float pdfVal;

    /// Compute each particle's compound probability of numLaserPts
    // independent  laser beam events.
    for(size_t eachPart = 0; eachPart < numParticles_; ++eachPart)
    {
        theParticles_[eachPart]->weight_ = 1.0; 
        /// Compute probability density function for each beam
        for (size_t beamIter = 0; beamIter < numLaserPts; ++beamIter)
        {
            pdfVal = 
            CommonMath::pdf(
                   theParticles_[eachPart]->laser_.scan_[beamIter],
                   laser.scan_[beamIter], sigma_); 

/*
        std::cout << "particle: " 
                  << theParticles_[eachPart]->laser_.scan_[beamIter] 
                  << std::endl;
        std::cout << "actual: " 
                  << laser.scan_[beamIter]
                  << std::endl;
        std::cout << "pdfVal: " 
                  << pdfVal 
                  << std::endl;
        std::cout << std::endl;
*/

        theParticles_[eachPart]->weight_ *= pdfVal;  
        }

        totalWeight_ += theParticles_[eachPart]->weight_;

/*
        std::cout << "weight: " << theParticles_[eachPart]->weight_ 
                  << std::endl;
*/

    }
/*
    std::cout << "totalWeight: " << totalWeight_ << std::endl;
    std::cout << std::endl;
*/
    //std::cout << std::endl;

}

void Particles::sampleAndReplace()
{
    // Create new set of particles:
    Particle** newParticles = new Particle*[numParticles_];
    for (size_t eachPart = 0; eachPart < numParticles_; ++eachPart)
        newParticles[eachPart] = new Particle{0,0,0};
    // Create an array to determine probability of picking a particle.
    float resampleProb[numParticles_];
    float currProb = 0;
    // Generate resample probabilities.

    for (size_t eachPart = 0; eachPart < numParticles_; ++eachPart)
    {
        currProb += (theParticles_[eachPart]->weight_ / totalWeight_); 
        resampleProb[eachPart] = currProb;
    }
    resampleProb[numParticles_ - 1] = 1.0;  /// Account for rounding error.


    // Generate a means to randomly choose particles based on weight.
    ///Note: these must be static or the same random values will pop out.
    static std::default_random_engine generator((unsigned int)time(0));
    static std::uniform_real_distribution<float> distribution(0,1);
    float randomVal;
    size_t pIter;


    for (size_t eachPart = 0; eachPart < numParticles_; ++eachPart)
    {
        randomVal = distribution(generator);
        //std::cout << "randomVal: " << randomVal << std::endl;
        pIter = 0;

        while (pIter < numParticles_)
        {
            if (randomVal < resampleProb[pIter])
            {
                // Add new particle based on probability.
                newParticles[eachPart]->pose_.x_ = 
                                        theParticles_[pIter]->pose_.x_;
                newParticles[eachPart]->pose_.y_ = 
                                        theParticles_[pIter]->pose_.y_;
                newParticles[eachPart]->pose_.theta_ = 
                                        theParticles_[pIter]->pose_.theta_;
                break;
            }
            else
                ++pIter;
        }
    } 

    // Delete old Particles:
    for (size_t eachPart = 0; eachPart < numParticles_; ++eachPart)
        delete theParticles_[eachPart];
    delete[] theParticles_;    

    // Replace with new particles.
    theParticles_ = newParticles; 
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
