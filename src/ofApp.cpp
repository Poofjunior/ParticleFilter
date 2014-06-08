#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){	
	ofBackground(ofColor::dimGray);	
	ofSetFrameRate(60);
    robotParticles_ = new Particles(100);
    robotParticles_->scatterParticles(windowX_, windowY_);

    // Create a map with one feature
    Map * theMap = new Map();
    theMap->addFeature("roomOutline.txt");
    
}

//--------------------------------------------------------------
void ofApp::update(){
}

//--------------------------------------------------------------
void ofApp::draw(){
	//ofFill();
	for (size_t eachPart = 0; eachPart < robotParticles_->numParticles_; 
        ++eachPart)
    {
        drawParticle(robotParticles_->theParticles_[eachPart]->xVal_, 
                     robotParticles_->theParticles_[eachPart]->yVal_,
                     robotParticles_->theParticles_[eachPart]->theta_);
    }
	

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

}

//--------------------------------------------------------------
void ofApp::drawParticle( float x, float y, float theta)
{
    ofPath myTri = ofPath();
    myTri.setFillColor(ofColor::cornsilk);
    
    // Create a triangle centered at the origin.
    myTri.triangle(-5,-2, 5, -2, 0, 12);
    // Rotate first, since rotation is about an axis. Then, translate
    myTri.rotate(theta, ofVec3f(0,0,1));
    myTri.translate(ofPoint(x, y, 0));
    myTri.draw();
}

