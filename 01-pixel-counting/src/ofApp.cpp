#include "ofApp.h"
void ofApp::setup(){
    ofBackground(255);
    
	width = 20;
	height = 10;
	pixels = new bool [width * height];
    
	for (int x = 0; x < width; x++){
		for (int y = 0; y < height; y++){
			pixels[y*width + x] = false;
		}
	}
	position = 0;
	helvetica.load("helvetica.otf", 15);
}
void ofApp::update(){
	for (int i = 0; i <width*height; i++){
		pixels[i] = false;
	}
	pixels[position] = true;
}
void ofApp::draw(){
	float widthPixel =  20;
	float heightPixel = 20;
	
	for (int x = 0; x < width; x++){
		for (int y = 0; y < height; y++){
			
            ofFill();
			if (pixels[y*width + x]) ofSetColor(0, 0, 0);
			else ofSetColor(255, 255, 255);
			ofDrawRectangle( 10 + x * widthPixel, 10 + y * heightPixel, widthPixel, heightPixel);
			
			ofNoFill();
			ofSetColor(0, 0, 0);
            ofDrawRectangle( 10 + x * widthPixel, 10 + y * heightPixel, widthPixel, heightPixel);
		}
	}
	ofSetColor(170,170,170);
	helvetica.drawString("position = " + ofToString(position), 25,250);
	helvetica.drawString("position / width (float) = " + ofToString((float) (position / (float)width), 3), 25,280);
	helvetica.drawString("(y) position / width (int) = " + ofToString((int) (position / (float)width)), 25,310);
	helvetica.drawString("(x) position % width = " + ofToString(position % width), 25,340);
	
	int x = (position % width);
	int y = (int) (position / (float)width);
	
	helvetica.drawString("y * width + x = " + ofToString(y*width + x), 25,370);
}
void ofApp::keyPressed(int key){
	switch (key){
		case OF_KEY_RIGHT:
			position++;
			break;
		case OF_KEY_LEFT:
			position--;
			break;
		case OF_KEY_UP:
			position-= width;
			break;
		case OF_KEY_DOWN:
			position+=width;
			break;
	}
	if (position < 0) position += (width*height);
	if (position >= width*height) position -= width*height;
}
