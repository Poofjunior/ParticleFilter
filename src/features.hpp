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
#include "point.hpp"

//TODO: add a forwardConnected_ array to indicate if there is a line from 
//      current  point to the next point and remove forwardConnectd_ from the 
//      point class.

/**
 * \class Feature
 * \brief generates a feature from an input *.txt file.
 * \details handles features as coordinates and lines drawn between them.
 *          Not all lines have points between them.
 */
class Feature {
    public:
    Feature(char* filepath);
    ~Feature();
        
    std::list<Point> points_;///< douubly-linked list of the feature's points
    // std::list front() and back() implementations are constant.

};
#endif // FEATURES_HPP
