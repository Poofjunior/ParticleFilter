#include "ofApp.h"
#include <iterator>

//--------------------------------------------------------------
void ofApp::setup(){	
	ofBackground(ofColor::dimGray);	
	ofSetFrameRate(60);
// TODO: enable this later
//    robotParticles_ = new Particles(5);
//    robotParticles_->initParticles(8,8);

    // Setup mapSegs_ path parameters
    mapSegs_.setFilled(false);
    mapSegs_.setStrokeColor(ofColor::lightSlateGrey);
    mapSegs_.setStrokeWidth(2);
    // Create a map with one feature
    theMap_ = new Map();
    theMap_->addFeature("roomOutline.txt");
    //theMap_->addFeature("box.txt");
    
// TODO: disable this later and remove testPart_ data member
    // for testing:
    //testPart_ = new Particle{1, 2.25, -1};
    testPart_ = new Particle{1.5, 3.9, -(M_PI/2.)};
    //testPart_ = new Particle{1.5, 2, -(M_PI/2.)}; // vertical laser works
    // FIXME: laser scanner returns inf insead of zero when on top of a wall
}

//--------------------------------------------------------------
void ofApp::update(){

    testPart_->laser_.takeScan(testPart_->pose_, *theMap_);
}

void ofApp::draw(){


    ofPath laser;
    Point laserLoc(testPart_->pose_.x_,testPart_->pose_.y_);
    Point intersection;
    laser.setFilled(false);
    laser.setStrokeColor(ofColor::red);
    laser.setStrokeWidth(1);


    for(size_t beamIter = 0; beamIter < testPart_->laser_.numPoints_; ++beamIter)
    {
        laser.moveTo(pixelsPerMeter_ * laserLoc.x_, 
                     pixelsPerMeter_ * laserLoc.y_);
        if(!(testPart_->laser_.scan_[beamIter] == 
           std::numeric_limits<float>::infinity()))
        {
            laser.lineTo(
               pixelsPerMeter_ * testPart_->laser_.intersections_[beamIter].x_,
               pixelsPerMeter_ * testPart_->laser_.intersections_[beamIter].y_);

/*
               std::cout << testPart_->laser_.intersections_[beamIter].x_ << ","
                        << testPart_->laser_.intersections_[beamIter].y_
                        << std::endl;
*/
        }
    }
    laser.draw();
    drawMap();


    // FIXME: change Map& to Map pointer... maybe.
    /*
    for (size_t numParts = 0; numParts < 5; ++numParts)
    {
    std::cout << "particle " << numParts << std::endl;
    robotParticles_->theParticles_[numParts]->laser_.takeScan(
                                    robotParticles_->theParticles_[numParts]->pose_,
                                    *theMap_);
    for (size_t i = 0; i < 
                        robotParticles_->theParticles_[numParts]->laser_.numPoints_;
                        ++i)
    std::cout << "dist: " 
              << robotParticles_->theParticles_[numParts]->laser_.scan_[i]
              << std::endl;

    }
    std::cout << std::endl;
    std::cout << std::endl;

    ofPath laser;
    Point laserLoc;
    Point intersection;
    laser.setFilled(false);
    laser.setStrokeColor(ofColor::red);
    laser.setStrokeWidth(1);

	for (size_t eachPart = 0; eachPart < robotParticles_->numParticles_; 
        ++eachPart)
    {
        // Draw arbitrary diagonal line for testing:
        Point segStart(0, 10);
        Point segEnd(windowX_, 600);

        drawParticle(robotParticles_->theParticles_[eachPart]->pose_.x_, 
                     robotParticles_->theParticles_[eachPart]->pose_.y_,
                     robotParticles_->theParticles_[eachPart]->pose_.theta_);

        Point laserLoc(robotParticles_->theParticles_[eachPart]->pose_.x_, 
                       robotParticles_->theParticles_[eachPart]->pose_.y_);

        LaserScanner::getIntersection(intersection, laserLoc,
                     robotParticles_->theParticles_[eachPart]->pose_.theta_,
                     segStart, segEnd);
        laser.moveTo
         (pixelsPerMeter_ * robotParticles_->theParticles_[eachPart]->pose_.x_,
          pixelsPerMeter_ * robotParticles_->theParticles_[eachPart]->pose_.y_);

        laser.lineTo(
            pixelsPerMeter_ * intersection.x_, 
            pixelsPerMeter_ * intersection.y_);
    }

    laser.draw();
    drawMap();
*/

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
            if (pointsIter->forwardConnected_)
            {   // check if last point needs to join with first point.
                if (*pointsIter == 
                    featureIter->points_.back())
                {   // draw a line from last point to first point
                    mapSegs_.lineTo(
                        pixelsPerMeter_ * featureIter->points_.front().x_, 
                        pixelsPerMeter_ * featureIter->points_.front().y_);
                }
                else
                {   // draw a line to the next point
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
    // Scale triangle appropriately.
    myTri.translate(ofPoint((x * pixelsPerMeter_), (y * pixelsPerMeter_), 0));
    myTri.draw();
}

