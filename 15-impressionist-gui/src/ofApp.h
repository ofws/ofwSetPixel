#pragma once
#include "ofMain.h"
#include "ofxGui.h"

class ofApp : public ofBaseApp{

public:
    void setup();
    void update();
    void draw();
    
    ofVideoGrabber vidGrabber;
    int	camWidth;
    int	camHeight;
    
    ofxPanel gui;
    ofxIntSlider comparisonThreshold, comparisonDistance, lineWidth, randomMul;
    ofxLabel frameRate;
};
