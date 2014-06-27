#include "ofApp.h"
#include <iterator>

//--------------------------------------------------------------
void ofApp::setup(){	
	ofBackground(ofColor::dimGray);	
	//ofSetFrameRate(60);
	ofSetFrameRate(60);

    robotParticles_ = new Particles(200);
    robotParticles_->initParticles(8,8);

    // Setup mapSegs_ path parameters
    mapSegs_.setFilled(false);
    mapSegs_.setStrokeColor(ofColor::lightSlateGrey);
    mapSegs_.setStrokeWidth(2);
    // Create a map with one feature
    theMap_ = new Map();
    theMap_->addFeature("roomOutline.txt");
    theMap_->addFeature("box.txt");
}

//--------------------------------------------------------------
void ofApp::update(){


    //getRealOdometryData()  /// OR fake it right here.
    /// FOR TESTING: make some fake wheel rotation data.
    MotionModel::rWheelDelta_ = 0.5; // in radians!
    MotionModel::lWheelDelta_ = 0.55;

    robotParticles_->propagateParticles();
    //robotParticles_->takeScan();
    //robotParticles_->scoreParticles();
    //robotParticles_->sampleAndReplace();
    robotParticles_->computeBestParticle();

    /// For illustration only
    /*
    robotParticles_->bestPart_.laser_.takeScan(
                            robotParticles_->bestPart_.pose_, 
                            *theMap_);
*/
}


void ofApp::draw(){

	for (size_t eachPart = 0; eachPart < robotParticles_->numParticles_; 
        ++eachPart)
    {
        drawParticle(robotParticles_->theParticles_[eachPart]->pose_.x_, 
                     robotParticles_->theParticles_[eachPart]->pose_.y_,
                     robotParticles_->theParticles_[eachPart]->pose_.theta_);
    }

   /// FOR TESTING: draw the laser. 
    //drawLaser(robotParticles_->bestPart_);
    drawParticle(robotParticles_->bestPart_.pose_.x_, 
                 robotParticles_->bestPart_.pose_.y_,
                 robotParticles_->bestPart_.pose_.theta_);
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


//--------------------------------------------------------------
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
    myTri.rotate(theta*(180./M_PI), ofVec3f(0,0,1));
    // Scale triangle appropriately.
    myTri.translate(ofPoint((x * pixelsPerMeter_), (y * pixelsPerMeter_), 0));
    myTri.draw();
}


//--------------------------------------------------------------
void ofApp::drawLaser(Particle& theParticle)
{
    ofPath laser;
    laser.setFilled(false);
    laser.setStrokeColor(ofColor::red);
    laser.setStrokeWidth(1);

    for(size_t beamIter = 0; beamIter < theParticle.laser_.numPoints_; 
        ++beamIter)
    {
        laser.moveTo(pixelsPerMeter_ * theParticle.pose_.x_, 
                     pixelsPerMeter_ * theParticle.pose_.y_);
        if(!(theParticle.laser_.scan_[beamIter] == 
           std::numeric_limits<float>::infinity()))
        {
            laser.lineTo(
             pixelsPerMeter_ * theParticle.laser_.intersections_[beamIter].x_,
             pixelsPerMeter_ * theParticle.laser_.intersections_[beamIter].y_);
        }
    }
    laser.draw();
}

