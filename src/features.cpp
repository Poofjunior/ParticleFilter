/**
 * features.cpp
 * \author Joshua Vasquez
 * \date June 7, 2014
 */
#include "features.hpp"

Feature::Feature(char *filepath)
{
    std::ifstream infile(filepath);
    // Format is x, y, forwardConnected 
    float x, y; 
    bool forwardConnected;
    std::cout << "Creating feature from " << filepath << std::endl;
    while (infile >> x >> y >> forwardConnected)
    {
        points_.push_back( Point{x,y,forwardConnected});
        std::cout << "(" << x << ", " << y << ")" << "forwardConnected: " << 
                     forwardConnected << std::endl;
    }
}

Feature::~Feature()
{
    // nothing to do! std::list will delete its contents correctly as long
    // as the contents isn't pointers. 
}
