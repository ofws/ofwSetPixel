#pragma once
#include "ofMain.h"
#include "ofxOpenCv.h"
#include "ofxFidMain.h"

class ofApp : public ofSimpleApp{
	
	public:
	
		ofVideoGrabber video;
		ofxCvGrayscaleImage grayImage;
		ofxCvGrayscaleImage grayBg;
		ofxCvGrayscaleImage	grayDiff;
		ofxCvColorImage	colorImg;
	
		ofxFiducialTracker fidfinder;
	
		int threshold;
		bool bLearnBakground;
		bool backgroundSubOn;
	
		
		void setup();
		void update();
		void draw();
		
		void keyPressed(int key);
		void keyReleased(int key);
		void mouseMoved(int x, int y );
		void mouseDragged(int x, int y, int button);
		void mousePressed(int x, int y, int button);
		void mouseReleased();
		
		
};

