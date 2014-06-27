/**
 * motionModel.hpp
 * \author Joshua Vasquez
 * \date June 12, 2014
 */

#ifndef MOTIONMODEL_HPP 
#define MOTIONMODEL_HPP
#include "pose.hpp"
#include "commonMath.hpp"
#include <ctgmath>

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

// TODO: add these as parameters in the constructor    
    static constexpr float wheelSpacing_ = 0.2;
    static constexpr float wheelRadius_ = 0.075;

private:
};
#endif // MOTIONMODEL_HPP


