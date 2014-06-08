#include "ofMain.h"
#include "ofApp.h"

//========================================================================
int main( ){

    ofApp* particleFilter =  new ofApp();
    ofSetupOpenGL(particleFilter->windowX_, particleFilter->windowY_, 
                  OF_WINDOW); 
    ofRunApp( particleFilter);

    // ofApp is deleted on exit.

}
