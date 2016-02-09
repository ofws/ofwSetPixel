#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
	ofSetVerticalSync(true);
	myPicture.load("test.png");
    myPicture.setImageType(OF_IMAGE_GRAYSCALE);
	
	//allocate an image the same size
	invertedPicture.allocate(myPicture.getWidth(), myPicture.getHeight(), OF_IMAGE_GRAYSCALE);
	
	// grab "pointers" to the pixels of the original and destination images. 
	unsigned char * origPixels =  myPicture.getPixels().getData();
	unsigned char * destPixels =  invertedPicture.getPixels().getData();
	
	int width = myPicture.getWidth();
	int height = myPicture.getHeight();
	
	// copy the pixels and invert
	for (int x = 0; x < width; x++){
		for (int y = 0; y < height; y++){
			int pixIndex = y * width + x;
			destPixels[pixIndex] = 255 - origPixels[pixIndex];
		}
	}
	
	// update makes sure the pixels are updated to the texture 
	// (if we alter the pixels of an image, we need to update to visually see the changes)
	invertedPicture.update();
    ofSetWindowShape(myPicture.getWidth()*2, myPicture.getHeight());
}
void ofApp::draw(){
	ofSetColor(255);
	myPicture.draw(0,0);
	invertedPicture.draw(myPicture.getWidth(), 0);
	
}

