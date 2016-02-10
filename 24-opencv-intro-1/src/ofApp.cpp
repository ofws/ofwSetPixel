#include "ofApp.h"

void ofApp::setup(){

    myPicture.load("test.png");
	myPicture.setImageType(OF_IMAGE_GRAYSCALE);
	
	// allocate opencv
	myPictureAsCvImage.allocate(myPicture.getWidth(), myPicture.getHeight());
    // load in
	myPictureAsCvImage.setFromPixels(myPicture.getPixels().getData(),myPicture.getWidth(), myPicture.getHeight());
	
    // flip vertically, not horizontally
	myPictureAsCvImage.mirror(true, false);
	
    // add brightness
	myPictureAsCvImage += 100;
    // blur
	myPictureAsCvImage.blur(11);
	
    ofSetWindowShape(myPicture.getWidth(), myPicture.getHeight());
}

void ofApp::draw(){
	
	ofSetColor(255);
	myPictureAsCvImage.draw(0,0);
}
