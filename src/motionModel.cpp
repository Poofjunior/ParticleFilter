/**
 * motionModel.cpp
 * \author Joshua Vasquez
 * \date June 12, 2014
 */

#include "motionModel.hpp"

float MotionModel::rWheelDelta_ = 0;
float MotionModel::lWheelDelta_ = 0;

float MotionModel::wheelSpacing_ = 0.25;
float MotionModel::wheelRadius_ = 0.1;

void MotionModel::updatePose(pose& thePose)
{
    // Do some math here based on rWheelDelta_ and lWheelDelta_.
    // FIXME: Change these to what they're supposded to be.
    thePose.x_ = 0; // = fancymath(thePose.x_) 
    thePose.y_ = 0; // = fancymath(thePose.x_) 
    thePose.theta_ = 0; // = fancymath(thePose.x_) 
    
    /// Reset deltas for next iteration.
    MotionModel::rWheelDelta_ = 0;
    MotionModel::lWheelDelta_ = 0;
    
}
