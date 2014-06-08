/**
 * map.cpp
 * \author Joshua Vasquez
 * \date June 7, 2014
 */
#include"map.hpp"

Map::Map()
    :numFeatures_{0}
{
    // nothing else to do!
}

Map::~Map()
{
// delete features?? std::list does this for us apparently.
}

void Map::addFeature(char *filepath)
{
    features_.push_back(Feature{filepath});
}

