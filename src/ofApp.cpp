#include "ofApp.h"
#include <iterator>

//--------------------------------------------------------------
void ofApp::setup(){	
	ofBackground(ofColor::dimGray);	
	ofSetFrameRate(60);
    robotParticles_ = new Particles(1);
    robotParticles_->initParticles(windowX_, windowY_);

    // Setup mapSegs_ path parameters
    mapSegs_.setFilled(false);
    mapSegs_.setStrokeColor(ofColor::lightSlateGrey);
    mapSegs_.setStrokeWidth(5);
    // Create a map with one feature
    theMap_ = new Map();
    theMap_->addFeature("roomOutline.txt");
    theMap_->addFeature("box.txt");
    
}

//--------------------------------------------------------------
void ofApp::update(){
}

void ofApp::draw(){

        ofPath laser;
        laser.setFilled(false);
        laser.setStrokeColor(ofColor::red);
        laser.setStrokeWidth(1);

    std::cout << std::endl;
	for (size_t eachPart = 0; eachPart < robotParticles_->numParticles_; 
        ++eachPart)
    {
        std::cout << "(" << robotParticles_->theParticles_[eachPart]->pose_.x_ 
                  << "," << robotParticles_->theParticles_[eachPart]->pose_.y_
                  << "," << 
                         robotParticles_->theParticles_[eachPart]->pose_.theta_
                  << ")" << std::endl;
        drawParticle(robotParticles_->theParticles_[eachPart]->pose_.x_, 
                     robotParticles_->theParticles_[eachPart]->pose_.y_,
                     robotParticles_->theParticles_[eachPart]->pose_.theta_);

        Point intersection;
        Point segStart(0, 10);
        Point segEnd(windowX_, 600);
        LaserScanner::getIntersection(intersection, 
                     robotParticles_->theParticles_[eachPart]->pose_.x_, 
                     robotParticles_->theParticles_[eachPart]->pose_.y_,
                     robotParticles_->theParticles_[eachPart]->pose_.theta_,
                     segStart, segEnd);
        laser.moveTo(robotParticles_->theParticles_[eachPart]->pose_.x_,
                     robotParticles_->theParticles_[eachPart]->pose_.y_);

        laser.lineTo(intersection.x_, intersection.y_);
    }

    laser.draw();
/*
    drawParticle(100, 100, 90);
    drawParticle(150, 100, 180);
    drawParticle(200, 100, 270);
*/
    drawMap();
}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button)
{}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button)
{}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button)
{}

void ofApp::drawMap()
{
    // iterate through list of features
    // draw each set of points with correct scaling.
    for (auto featureIter = theMap_->features_.begin(); 
              featureIter != theMap_->features_.end();
              ++featureIter)
    {
        // moveTo first point.
        mapSegs_.moveTo( pixelsPerMeter_ * featureIter->points_.front().x_, 
                         pixelsPerMeter_ * featureIter->points_.front().y_);

        for (auto pointsIter = (*featureIter).points_.begin();
                  pointsIter != (*featureIter).points_.end();
                  ++pointsIter)
        {
            if (pointsIter->lineToNext_)
            {
                // check if last point needs to join with first point.
                if (*pointsIter == 
                    featureIter->points_.back())
                {   // draw a line from last point to first point
                    mapSegs_.lineTo(
                        pixelsPerMeter_ * featureIter->points_.front().x_, 
                        pixelsPerMeter_ * featureIter->points_.front().y_);
                }
                else
                {
                    // draw a line to the next point
                    mapSegs_.lineTo(
                        pixelsPerMeter_ * (std::next(pointsIter,1))->x_,  
                        pixelsPerMeter_ * (std::next(pointsIter,1))->y_);  
                }
            }
                    
        }
    }
    mapSegs_.draw();

}

//--------------------------------------------------------------
void ofApp::drawParticle( float x, float y, float theta)
{
    ofPath myTri = ofPath();
    myTri.setFillColor(ofColor::cornsilk);
    
    // Create a triangle centered at the origin.
    myTri.triangle(-2, -5, -2, 5, 12, 0);
    // Rotate first, since rotation is about an axis. Then, translate
    myTri.rotate(theta, ofVec3f(0,0,1));
    myTri.translate(ofPoint(x, y, 0));
    myTri.draw();
}

