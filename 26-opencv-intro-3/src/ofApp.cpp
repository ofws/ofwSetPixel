#include "ofApp.h"

void ofApp::setup(){
	myPicture.load("test.png");
	myPicture.setImageType(OF_IMAGE_GRAYSCALE);
	
	myPictureAsCvImage.allocate(myPicture.getWidth(), myPicture.getHeight());
	myPictureAsCvImage.setFromPixels(myPicture.getPixels().getData(),myPicture.getWidth(), myPicture.getHeight());
    ofSetWindowShape(myPicture.getWidth(), myPicture.getHeight());
}

void ofApp::update(){
	myPictureAsCvImage.setFromPixels(myPicture.getPixels().getData(),myPicture.getWidth(), myPicture.getHeight());
	
	if (mouseX > 0) myPictureAsCvImage.blur(mouseX * 2 + 1);
	myPictureAsCvImage.threshold(mouseY);
	
}
void ofApp::draw(){
	ofSetColor(255);
	myPictureAsCvImage.draw(0,0);
}