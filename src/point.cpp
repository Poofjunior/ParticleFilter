/**
 * point.cpp
 * \author Joshua Vasquez
 * \date June 12, 2014
 */
#include "point.hpp"

    // TODO: remove fowardConnected_ entirely and implement solely in features
    // class.
Point::Point(float x, float y, bool forwardConnected)
    :x_{x}, y_{y}, forwardConnected_{forwardConnected}
{
    // nothing else to do!
}

Point::~Point()
{}

bool Point::operator==(const Point& otherPoint)
{
/*
    return (x_ == otherPoint.x_) && (y_ == otherPoint.y_) && 
           (forwardConnected_== otherPoint.forwardConnected_); 
*/
    return (x_ == otherPoint.x_) && (y_ == otherPoint.y_);
           
}
