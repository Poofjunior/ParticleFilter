#include <unistd.h> // for sleep function
#include "particles.hpp"
#include "particle.hpp"
#include "map.hpp"
#include "motionModel.hpp"
#include "laserScanner.hpp"
#include <iostream> // TODO: remove after debugging
#include <cstdlib>
#include <iterator>

//========================================================================
int main( ){

// Create the Particles.
    Particles* robotParticles_;

    robotParticles_ = new Particles(1000);
    robotParticles_->initParticles(10,10);
    
    Particle simBot(4.1,3.5, 0, 0);
    
    Map theMap_;
    theMap_.addFeature("bigMap.txt");

    size_t i = 180;
    while(i--)
    {
    // Main loop execution here: (don't forget to delay till 1/30th sec has
    // elapsed)
    // Fake some wheel data:

        robotParticles_->propagateParticles();
        simBot.propagate();

        robotParticles_->takeScan(theMap_);
        simBot.laser_.takeScan(simBot.pose_,
                                 theMap_);

        // Score particles against the simulated robot's laser.
             robotParticles_->scoreParticles(simBot.laser_);
        if((MotionModel::rWheelDelta_ != 0) || (MotionModel::lWheelDelta_ = 0))
        {
            robotParticles_->sampleAndReplace();
        }

        sleep(0.0333);
    }

    delete robotParticles_;
    std::exit(0);
}
