/**
 * point.cpp
 * \author Joshua Vasquez
 * \date June 12, 2014
 */
#include "point.hpp"

    // TODO: remove lineToNext entirely and implement solely in features
    // class.
Point::Point(float x, float y, bool lineTo)
    :x_{x}, y_{y}, lineToNext_{lineTo}
{
    // nothing else to do!
}

Point::~Point()
{}

bool Point::operator==(const Point& otherPoint)
{
/*
    return (x_ == otherPoint.x_) && (y_ == otherPoint.y_) && 
           (lineToNext_ == otherPoint.lineToNext_); 
*/
    return (x_ == otherPoint.x_) && (y_ == otherPoint.y_);
           
}
