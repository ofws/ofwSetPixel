#include "ofApp.h"
void ofApp::setup(){
	ofSetVerticalSync(true);
	myPicture.load("test.png");
	myPicture.setImageType(OF_IMAGE_GRAYSCALE);
    modifiedPicture.allocate(myPicture.getWidth(), myPicture.getHeight(), OF_IMAGE_GRAYSCALE);
	
	int width = myPicture.getWidth();
	int height = myPicture.getHeight();
	
	// grab "pointers" to the pixels of the original and destination images. 
	unsigned char * origPixels =  myPicture.getPixels().getData();
	unsigned char * destPixels =  modifiedPicture.getPixels().getData();
	
	// copy the pixels in and upload
	for (int x = 0; x < width; x++){
		for (int y = 0; y < height; y++){
			int pixIndex = y * width + x;
			destPixels[pixIndex] = origPixels[pixIndex];
		}
	}
	modifiedPicture.update();
    ofSetWindowShape(myPicture.getWidth()*2, myPicture.getHeight());
}
void ofApp::update(){
	int width = myPicture.getWidth();
	int height = myPicture.getHeight();
	
	// grab "pointers" to the pixels of the original and destination images. 
	unsigned char * origPixels =  myPicture.getPixels().getData();
	unsigned char * destPixels =  modifiedPicture.getPixels().getData();
	
	// copy the pixels in and upload
	for (int x = 0; x < width; x++){
		for (int y = 0; y < height; y++){
			
			int pixIndex = y * width + x;
			int pixSource = (y + (int)ofRandom(-mouseY, mouseY)) * width + (x +  (int)ofRandom(-mouseX, mouseX));
			if (pixSource < 0) pixSource = 0;
			if (pixSource >= width*height) pixSource = width*height-1;
			destPixels[pixIndex] = origPixels[pixSource];
		}
	}
	modifiedPicture.update();
}
void ofApp::draw(){
	ofSetColor(255);
	myPicture.draw(0,0);
	modifiedPicture.draw(myPicture.getWidth(), 0);
	
}
