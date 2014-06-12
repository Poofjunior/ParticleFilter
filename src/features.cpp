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

Feature::Point::Point(float x, float y, bool lineTo)
    :x_{x}, y_{y}, lineToNext_{lineTo}
{
    // nothing else to do!
}

Feature::Point::~Point()
{}

bool Feature::Point::operator==(const Point& otherPoint)
{
    return (x_ == otherPoint.x_) && (y_ == otherPoint.y_) && 
           (lineToNext_ == otherPoint.lineToNext_); 
}