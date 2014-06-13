/**
 * features.cpp
 * \author Joshua Vasquez
 * \date June 7, 2014
 */
#include "features.hpp"

Feature::Feature(char *filepath)
{
    std::ifstream infile(filepath);
    // Format is x, y, lineToNext
    float x, y; 
    bool lineToNext;
    std::cout << "Creating feature from " << filepath << std::endl;
    while (infile >> x >> y >> lineToNext)
    {
        points_.push_back( Point{x,y,lineToNext});
        std::cout << "(" << x << ", " << y << ")" << "lineToNext: " << 
                     lineToNext << std::endl;
    }
}

Feature::~Feature()
{
    // nothing to do! std::list will delete its contents correctly as long
    // as the contents isn't pointers. 
}
