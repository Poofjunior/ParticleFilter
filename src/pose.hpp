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
    Pose(float x = 0, float y = 0, float theta = 0) 
    :x_(x), y_(y), theta_(theta)
    {
        // Nothing else to do!
    }
    ~Pose()
    {
        // Nothing else to do!
    }

    float x_;
    float y_;
    float theta_;

};
#endif // POSE_HPP 


