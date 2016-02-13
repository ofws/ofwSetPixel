#pragma once

#include "ofMain.h"
//#include "ofxCvMain.h"
#include "ofxOpenCv.h"
//#include "ofxFidMain.h"
#include "ofxFiducialTracker.h"

class ofApp : public ofSimpleApp{
	
	public:
	
		ofVideoGrabber 		vidGrabber;
		ofxCvGrayscaleImage grayImage;
		ofxCvColorImage		colorImg;
	
		ofxFiducialTracker	fidfinder;
	
		int 				threshold;
	
		
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