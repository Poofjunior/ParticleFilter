/**
 * pose.hpp
 * \author Joshua Vasquez
 * \date June 12, 2014
 */

#ifndef POSE_HPP 
#define POSE_HPP

/**
 * \class pose 
 * \brief a motion model class unique to a differential drive train robot
 */
class Pose {

public:
    Pose();
    ~Pose();

    float x_;
    float y_;
    float theta_;

};
#endif // POSE_HPP 


