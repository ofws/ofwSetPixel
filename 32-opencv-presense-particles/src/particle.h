#pragma once


#include "ofMain.h"
#include "ofxOpenCv.h"

class particle {

	public: 
	ofPoint pos;
	float energy;
	void setup();
	void update();
	void draw();
	
	void checkImage( ofxCvGrayscaleImage * myImage);
};