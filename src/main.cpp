#include "ofMain.h"
#include "ofApp.h"
#include <cstdlib>

//========================================================================
int main( ){

// bulk of the top-level code is in the update() and draw() member functions
// of ofApp.cpp

    ofApp* particleFilter =  new ofApp();
    ofSetupOpenGL(particleFilter->windowX_, particleFilter->windowY_, 
                  OF_WINDOW); 

    ofRunApp( particleFilter);
    
    delete particleFilter;

    // ofApp is deleted on exit.
    std::exit(2);

}
