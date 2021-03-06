/**
 * map.hpp
 * \author Joshua Vasquez
 * \date June 7, 2014
 */

#ifndef MAP_HPP 
#define MAP_HPP
#include "features.hpp"
#include <stdlib.h>
#include <list>

// Features:
class Map {
public:
    Map();
    ~Map();
    Map(const Map& otherMap) = delete;
    Map& operator=(const Map& otherMap) = delete;

/**
 * \fn addFeature(char *fileName)
 * \brief create a new feature from information in the *.txt file.
 */
    void addFeature(char *filepath);
    
    size_t numFeatures_;

    std::list<Feature> features_;
    
};
#endif // MAP_HPP 



