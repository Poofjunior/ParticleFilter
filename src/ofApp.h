/**
 * ofApp.h
 * \author The OF Team with some edits by Joshua Vasquez
 * \date June 8, 2014
 */
#pragma once

#include "ofMain.h"
#include "particles.hpp"
#include "map.hpp"
#include <iostream> // FIXME: remove after debugging

class ofApp : public ofBaseApp{

    public:
        static const int windowX_ = 800;
        static const int windowY_ = 600;
                      
        Particles* robotParticles_;
        Map* theMap_;
        ofPath mapSegs_;
    
        void setup();
        void update();
        void draw();
        
        void mouseDragged(int x, int y, int button);
        void mousePressed(int x, int y, int button);
        void mouseReleased(int x, int y, int button);
    
/**
 * \fn drawMap()
 * \brief iterates through all features and draws them
 * \details features must be added in the ofApp.cpp setup function.
 */
        void drawMap();

/**
 * \fn drawParticles( float x, float y, float theta)
 * \brief iterates through all particles and draws them.
 */
        void drawParticle( float x, float y, float theta);

    private:
        static constexpr float pixelsPerMeter_ = 100.;
};

