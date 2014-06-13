/**
 * point.hpp
 * \author Joshua Vasquez
 * \date June 12, 2014
 */

#ifndef POINT_HPP 
#define POINT_HPP 

/**
 * \class Point
 * \brief a mini class of basically just coordinates
 * \details each point also indicates whether or not there is a line to the 
 *          next point
 */
class Point {
    public:
        Point(float x, float y, bool lineTo = false);
        ~Point();
        bool operator==(const Point& otherPoint); ///< overload equality
        float x_;
        float y_;
        bool lineToNext_;   ///< true if point is connected to next point
    };
#endif // POINT_HPP 
