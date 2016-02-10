#include "ofApp.h"

void ofApp::setup(){
	myPicture.load("test.png");
    myPicture.setImageType(OF_IMAGE_GRAYSCALE);
	
	// allocate opencv, load in:
    // these two lines basically do the same thing
    myPictureAsCvImage.allocate(myPicture.getWidth(), myPicture.getHeight());
//	myPictureAsCvImage.setFromPixels(myPicture.getPixels().getData(),myPicture.getWidth(), myPicture.getHeight());
	
    ofSetWindowShape(myPicture.getWidth(), myPicture.getHeight());
}

void ofApp::update(){
	
    // always refers back to the original image before threshold
	myPictureAsCvImage.setFromPixels(myPicture.getPixels().getData(),myPicture.getWidth(), myPicture.getHeight());
	myPictureAsCvImage.threshold(mouseX);
}

void ofApp::draw(){
	ofSetColor(255);
	myPictureAsCvImage.draw(0,0);
}
