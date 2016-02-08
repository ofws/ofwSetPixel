#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){

	// load the image from the data folder
	myPicture.loadImage("test.png");
	
	// set the image type to be grayscale (1 byte per pixel)
	myPicture.setImageType(OF_IMAGE_GRAYSCALE);
	
	// allocate opencv, load in: 
	myPictureAsCvImage.allocate(myPicture.width, myPicture.height);
	myPictureAsCvImage.setFromPixels(myPicture.getPixels(),myPicture.width, myPicture.height);
	
	myPictureAsCvImage.mirror(true, false);
	
	myPictureAsCvImage += 100;
	myPictureAsCvImage.blur(11);
	
	// set background color to be white: 
	ofBackground(255, 255, 255);
}

//--------------------------------------------------------------
void ofApp::update(){
		
}

//--------------------------------------------------------------
void ofApp::draw(){
	
	// when we draw, the drawing color "tints" the drawing, so white is best for image
	// ie, white = no tint.
	ofSetColor(255, 255, 255);
	myPictureAsCvImage.draw(0,0);
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

