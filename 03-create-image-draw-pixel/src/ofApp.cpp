#include "ofApp.h"
void ofApp::setup(){
	ofBackground(255);
	width = 400;
	height = 400;
    image.allocate(width, height, OF_IMAGE_GRAYSCALE);
	
    unsigned char * pixels =  image.getPixels().getData();
	for (int i = 0; i < width * height; i++){
		pixels[i] = 0;
	}
	image.update();
    
    ofSetWindowShape(width, height);
}
void ofApp::update(){
	unsigned char * pixels =  image.getPixels().getData();
	if (mouseX >= 0 && mouseX < width){
		if (mouseY >= 0 && mouseY < height){
			int pixelPosition = mouseY * width + mouseX;
			pixels[pixelPosition] = 255;
		}
	}
	image.update();
}
void ofApp::draw(){
	image.draw(0,0);
}
