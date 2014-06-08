#pragma once

#include "ofMain.h"
#include "particles.hpp"
#include "map.hpp"

class ofApp : public ofBaseApp{

    public:
        static const int windowX_ = 800;
        static const int windowY_ = 600;
                      
        Particles* robotParticles_;
    
        void setup();
        void update();
        void draw();
        
        void mouseDragged(int x, int y, int button);
        void mousePressed(int x, int y, int button);
        void mouseReleased(int x, int y, int button);
    
        void drawMap();
        void drawParticle( float x, float y, float theta);
    private:
        static constexpr float pixelsPerMeter_ = 100.;
};


