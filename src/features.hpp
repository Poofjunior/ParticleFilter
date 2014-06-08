/**
 * features.hpp
 * \author Joshua Vasquez
 * \date June 7, 2014
 */

#ifndef FEATURES_HPP
#define FEATURES_HPP
#include <list>
#include <fstream>
#include <iostream>

/**
 * \class Feature
 * \brief a linked list of points detailing how to draw a feature on the map.
 * \details points may or may not be joined by segments.
 */
class Feature {
    public:
/**
 * \class Feature
 * \brief generates a feature from an input *.txt file.
 * \details handles features as coordinates and lines drawn between them.
 *          Not all lines have points between them.
 */
    Feature(char* filepath);
    ~Feature();
/**
 * \class Point
 * \brief a mini class of basically just coordinates
 * \details each point also indicates whether or not there is a line to the 
 *          next point
 */
    class Point {
        public:
            Point(float x, float y, bool lineTo);
            ~Point();
            float x_;
            float y_;
            bool lineToNext_;   ///< true if point is connected to next point
    };
        
    std::list<Point> points_;///< douubly-linked list of the feature's points
    // std::list front() and back() implementations are constant.

};
#endif // FEATURES_HPP
