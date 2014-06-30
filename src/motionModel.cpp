/**
 * motionModel.cpp
 * \author Joshua Vasquez
 * \date June 12, 2014
 */

#include "motionModel.hpp"

/**
 * \brief static class member definitions
 */
float MotionModel::rWheelDelta_;
float MotionModel::lWheelDelta_;

MotionModel::MotionModel()
{
    // nothing to default initialize!
}

MotionModel::~MotionModel()
{
    // nothing to do!
}

void MotionModel::updatePose(Pose& thePose, bool noise)
{
    float dSR;
    float dSL;
    if (noise)
    {
        /// Note: these must be static or repeated calls will have the
        ///       same randomness!
        static std::default_random_engine generator_((unsigned int) time(0));
        static std::normal_distribution<float>distribution_(0,.1);

        float wheelNoiseL = distribution_(generator_);
        float wheelNoiseR = distribution_(generator_);
        //std::cout << "wheelNoise: " << wheelNoise << std::endl; 

        // Do some math here based on rWheelDelta_ and lWheelDelta_.
        dSR = rWheelDelta_ * wheelRadius_ + 
                    rWheelDelta_* wheelNoiseR;
        dSL = lWheelDelta_ * wheelRadius_ + 
                    lWheelDelta_ * wheelNoiseL;
    }
    else
    {
        dSR = rWheelDelta_ * wheelRadius_; 
        dSL = lWheelDelta_ * wheelRadius_; 
    }

    float dS = (dSR + dSL)/2.0;

    float dT = (dSR - dSL)/wheelSpacing_;
    float dX = dS * cos(thePose.theta_ + (dT/2.0));
    float dY = dS * sin(thePose.theta_ + (dT/2.0));

    thePose.x_ += dX; 
    thePose.y_ += dY; 
    thePose.theta_ = CommonMath::tuneAngle(thePose.theta_ + dT); 
    

}
