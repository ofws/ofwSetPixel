#include "ofApp.h"

void ofApp::setup(){

	myPicture.load("test.png");
	myPicture.setImageType(OF_IMAGE_GRAYSCALE);
    ofBackground(0, 0, 0);
	// this prevents banding on mac (vertical sync)
	ofSetVerticalSync(true);
    ofSetWindowShape(myPicture.getWidth()*2, myPicture.getHeight());
}
void ofApp::draw(){
	
	ofSetColor(255);
	myPicture.draw(0,0);
	
	// get a pointer to the image data:
	unsigned char * pixelsFromImage = myPicture.getPixels().getData();
	int width = myPicture.getWidth();
	int height = myPicture.getHeight();
	
	// copy the pixels in and upload
	for (int x = 0; x < width; x+=20){
		for (int y = 0; y < height; y+=20){
			int pixIndex = y * width + x;
			int pixVal = pixelsFromImage[pixIndex];
			float pct = (float)pixVal / 255.0f;
			ofDrawCircle(width + 10 + x, y, 10*pct);
		}
	}
	
	
	
}
