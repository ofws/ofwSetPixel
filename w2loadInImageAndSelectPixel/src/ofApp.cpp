#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){

	// load the image from the data folder
	myPicture.loadImage("test.png");
	
	// set the image type to be grayscale (1 byte per pixel)
	myPicture.setImageType(OF_IMAGE_GRAYSCALE);
	
	// set background color to be white: 
	ofBackground(255, 255, 255);
	
	// this prevents banding on mac (vertical sync)
	ofSetVerticalSync(true);
}

//--------------------------------------------------------------
void ofApp::update(){

}

//--------------------------------------------------------------
void ofApp::draw(){
	

	// when we draw, the drawing color "tints" the drawing, so white is best for image
	// ie, white = no tint.
	ofSetColor(255, 255, 255);
	myPicture.draw(0,0);
	
	if (mouseX >= 0 && mouseX < myPicture.width){
		if (mouseY >= 0 && mouseY < myPicture.height){	
			unsigned char * pixels = myPicture.getPixels();
			int whichPixel = mouseY * myPicture.width + mouseX;
			int color = pixels[whichPixel];
			ofSetColor(color, color, color);
			ofFill();
			ofRect(myPicture.width, 0, myPicture.width, myPicture.height);
		}
	}
	
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){

}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){

}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){

}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h){

}

