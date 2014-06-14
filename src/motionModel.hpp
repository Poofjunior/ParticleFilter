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
class MotionModel {
public:
    MotionModel();
    ~MotionModel();
    static void updatePose(Pose& oldPose);

    static float rWheelDelta_;
    static float lWheelDelta_;
    
    static constexpr float wheelSpacing_ = 0.25;
    static constexpr float wheelRadius_ = 0.1;

private:
};
#endif // MOTIONMODEL_HPP


