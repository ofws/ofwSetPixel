#include "ofApp.h"
void ofApp::setup(){

	myPicture.load("test.png");
	myPicture.setImageType(OF_IMAGE_GRAYSCALE);
    ofSetWindowShape(myPicture.getWidth()*2, myPicture.getHeight());
}
void ofApp::draw(){
	ofSetColor(255);
	myPicture.draw(0,0);
	
	if (mouseX >= 0 && mouseX < myPicture.getWidth()){
		if (mouseY >= 0 && mouseY < myPicture.getHeight()){	
			unsigned char * pixels = myPicture.getPixels().getData();
			int whichPixel = mouseY * myPicture.getWidth() + mouseX;
			int color = pixels[whichPixel];
			ofSetColor(color, color, color);
			ofFill();
			ofDrawRectangle(myPicture.getWidth(), 0, myPicture.getWidth(), myPicture.getHeight());
		}
	}
}
