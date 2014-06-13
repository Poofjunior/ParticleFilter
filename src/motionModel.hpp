/**
 * motionModel.hpp
 * \author Joshua Vasquez
 * \date June 12, 2014
 */

#ifndef MOTIONMODEL_HPP 
#define MOTIONMODEL_HPP
#include "pose.hpp"

/**
 * \namespace MotionModel 
 * \brief a motion model namespace unique to a differential drive train robot
 * \details rWheelDelta and lWheelDelta should be reassigned at each loop 
 *          iteration before calling updatePose.
 */
namespace MotionModel {

    float rWheelDelta_;
    float lWheelDelta_;
    float wheelSpacing_;
    float wheelRadius_;
    
    void updatePose(Pose& oldPose);
};
#endif // MOTIONMODEL_HPP


