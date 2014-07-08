/**
 * ofApp.h
 * \author The OF Team with some edits by Joshua Vasquez
 * \date June 8, 2014
 */
#pragma once

#include "ofMain.h"
#include "particles.hpp"
#include "particle.hpp"
#include "map.hpp"
#include "motionModel.hpp"
#include "laserScanner.hpp"
#include <iostream> // TODO: remove after debugging

class ofApp : public ofBaseApp, public ofThread{

    public:
        static const int windowX_ = 1000;
        static const int windowY_ = 1000;
                      
        Particles* robotParticles_;
        Particle* simBot_;  /// a simulated robot that can stand in
        Map* theMap_;
        ofPath mapSegs_;

    
        void setup();
        void update();
        void draw();
        void threadedFunction();
        void exit();
    
        
        void mouseDragged(int x, int y, int button);
        void mousePressed(int x, int y, int button);
        void mouseReleased(int x, int y, int button);
        void keyPressed(int key);
    
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

/**
 * \fn void drawLaser( Particle& particle)
 *  \brief draws the laser for a particle
 */
        void drawLaser(Particle& theParticle);

    private:
        static constexpr float pixelsPerMeter_ = 100.;
        bool runCalc_;
};


