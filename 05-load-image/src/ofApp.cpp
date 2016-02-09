#include "ofApp.h"
void ofApp::setup(){
	// load the image from the data folder
	myPicture.load("test.png");
	// set the image type to be grayscale (1 byte per pixel)
	myPicture.setImageType(OF_IMAGE_GRAYSCALE);
    ofSetWindowShape(myPicture.getWidth(), myPicture.getHeight());
}
void ofApp::draw(){
	// when we draw, the drawing color "tints" the drawing, so white is best for image
	// ie, white = no tint.
	ofSetColor(255);
	myPicture.draw(0,0);
}
