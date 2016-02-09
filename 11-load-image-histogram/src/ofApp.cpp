#include "ofApp.h"

void ofApp::setup(){
	myPicture.load("test.png");
	myPicture.setImageType(OF_IMAGE_GRAYSCALE);
	
	for (int i = 0; i < 256; i++){
		histogramValues[i] = 0;
	}
	
	int width = myPicture.getWidth();
	int height = myPicture.getHeight();
	unsigned char * pixels = myPicture.getPixels().getData();
    
    //fill histogram array for each pixel in that value
	for (int x = 0; x < width; x++){
		for (int y = 0; y < height; y++){
			int pixVal = pixels[y*width + x];
			histogramValues[pixVal]++;
		}
	}
    
    ofSetWindowShape(myPicture.getWidth()+256, myPicture.getHeight());
}

void ofApp::draw(){
    ofBackgroundGradient(ofColor(80), ofColor::black);
	ofSetColor(255);
	myPicture.draw(0,0);
	
	//find max value from array
	int maxVal = 0;
	for (int i = 0; i < 256; i++){
		if (histogramValues[i] > maxVal){
			maxVal = histogramValues[i];
		}
	}
	
    ofSetColor(ofColor::navajoWhite);
	for (int i = 0; i < 256; i++){
		float pct = (float)histogramValues[i] / (float)maxVal;
        float xPos = i + myPicture.getWidth();
		ofDrawLine(xPos, ofGetHeight(), xPos, ofGetHeight() - (pct*200));
	}
}
