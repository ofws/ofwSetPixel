#include "ofApp.h"
void ofApp::setup(){
	myPicture.load("test.png");
	myPicture.setImageType(OF_IMAGE_GRAYSCALE);
	modifiedPicture.allocate(myPicture.getWidth(), myPicture.getHeight(), OF_IMAGE_GRAYSCALE);
    ofSetWindowShape(myPicture.getWidth()*2, myPicture.getHeight());
}
void ofApp::update(){
	int width = myPicture.getWidth();
	int height = myPicture.getHeight();
	
	cout << "mouse = " << mouseX << endl;
	
	// grab "pointers" to the pixels of the original and destination images. 
	unsigned char * origPixels =  myPicture.getPixels().getData();
	unsigned char * destPixels =  modifiedPicture.getPixels().getData();
	
	// copy the pixels in and upload
	for (int x = 0; x < width; x++){
		for (int y = 0; y < height; y++){
			int pixIndex = y * width + x;
			if (origPixels[pixIndex] > mouseX){
				destPixels[pixIndex] = 255;
			} else {
				destPixels[pixIndex] = 0;
			}
		}
	}
	modifiedPicture.update();
}
void ofApp::draw(){
	ofSetColor(255);
	myPicture.draw(0,0);
	
	modifiedPicture.draw(myPicture.getWidth(), 0);
}



