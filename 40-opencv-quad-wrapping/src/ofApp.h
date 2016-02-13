#pragma once

#include "ofMain.h"
#include "ofxOpenCv.h"
#include "ofxGui.h"

// uncomment this to use a live camera
// otherwise, we'll use a movie file
#define _USE_LIVE_VIDEO

class ofApp : public ofBaseApp{
public:
    
    void setup();
    void update();
    void draw();

    void keyPressed (int key);
    void mousePressed(int x, int y, int button);
    void mouseDragged(int x, int y, int button);

    ofxPanel gui;
    ofxToggle bLearnBg;
    ofxIntSlider threshold, minBlobSize;
    ofxIntSlider maxBlobSize, nBlobsConsidered;
    
    ofxLabel framerate;
    
    int width, height;
    
    #ifdef _USE_LIVE_VIDEO
      ofVideoGrabber video;
    #else
      ofVideoPlayer video;
    #endif

    ofxCvColorImage	colorImg;

    ofxCvGrayscaleImage grayImage;
    ofxCvGrayscaleImage grayImagePreWarp;
    ofxCvGrayscaleImage grayBg;
    ofxCvGrayscaleImage grayDiff;

    ofPoint	srcPts[4];
    ofPoint	dstPts[4];
    ofPoint wrapOffset;

    ofxCvContourFinder 	contourFinder;

    bool bAdjustingPoint;
    int	whichPointAdjusting;
	
};

