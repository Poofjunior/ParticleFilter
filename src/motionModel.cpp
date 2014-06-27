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
    float dS = (rWheelDelta_ + lWheelDelta_)/2.0;

    float dT = (rWheelDelta_ - lWheelDelta_)/wheelSpacing_;
    float dX = dS * cos(thePose.theta_ + (dT/2.0));
    float dY = dS * sin(thePose.theta_ + (dT/2.0));

    // FIXME: Change these to what they're supposded to be.
    thePose.x_ += dX; 
    thePose.y_ += dY; 
    thePose.theta_ = CommonMath::tuneAngle(thePose.theta_ + dT); 
    

}
