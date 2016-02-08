#include "ofApp.h"
void ofApp::setup(){
	
	ofBackground(255, 255, 255);
	// ---- (1) pick a width and height:
	width = 400;
	height = 250;
	// ---- (2) allocate an image
	image.allocate(width, height, OF_IMAGE_GRAYSCALE);
	// ---- (3) grab a "pointers" to the pixels of the image
	unsigned char * pixels =  image.getPixels().getData();
	// ---- (4) put random values into memory...  be careful with your for loops when you start to alter memory
	for (int i = 0; i < width * height; i++){
		pixels[i] = (int)ofRandom(0,255);
	}
	// ---- (5) tell the image to update it's texture from it's pixels so that we can see the change
	image.update();
    
    ofSetWindowShape(width, height);
}
void ofApp::update(){
	unsigned char * pixels =  image.getPixels().getData();
	for (int i = 0; i < width * height; i++){
		pixels[i] = (int)ofRandom(127-mouseX, 127+mouseX);
	}
	image.update();
}
void ofApp::draw(){
    image.draw(0,0);
}

