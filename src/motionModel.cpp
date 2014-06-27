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

void MotionModel::updatePose(Pose& thePose)
{
    // Do some math here based on rWheelDelta_ and lWheelDelta_.
    float dSR = rWheelDelta_ * wheelRadius_;
    float dSL = lWheelDelta_ * wheelRadius_;
    float dS = (dSR + dSL)/2.0;

    float dT = (dSR - dSL)/wheelSpacing_;
    float dX = dS * cos(thePose.theta_ + (dT/2.0));
    float dY = dS * sin(thePose.theta_ + (dT/2.0));

    thePose.x_ += dX; 
    thePose.y_ += dY; 
    thePose.theta_ = CommonMath::tuneAngle(thePose.theta_ + dT); 
    

}
