/**
 * motionModel.cpp
 * \author Joshua Vasquez
 * \date June 12, 2014
 */

#include "motionModel.hpp"
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
    // FIXME: Change these to what they're supposded to be.
    thePose.x_ = 0; // = fancymath(thePose.x_) 
    thePose.y_ = 0; // = fancymath(thePose.x_) 
    thePose.theta_ = 0; // = fancymath(thePose.x_) 

}
