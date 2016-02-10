#pragma once
#include "ofMain.h"
#include "ofxGui.h"

class ofApp : public ofBaseApp{

public:
    void setup();
    void update();
    void draw();
    void keyPressed(int key);
    
    ofVideoGrabber vidGrabber;
    int	camWidth;
    int	camHeight;
    
    ofxPanel gui;
    ofxIntSlider comparisonThreshold, comparisonDistance, lineWidth, randomMul;
    ofxLabel instruction, frameRate;
    bool bHide;
};
