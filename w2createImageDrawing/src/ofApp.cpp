#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
	
	ofBackground(255, 255, 255);
	

	// ---- (1) pick a width and height: 
	
	width = 400;
	height = 400;
	
	// ---- (2) allocate an image
	
	image.allocate(width, height, OF_IMAGE_GRAYSCALE);
	
	
	// ---- (3) grab a "pointers" to the pixels of the image
	
	unsigned char * pixels =  image.getPixels();
	
	// ---- (4) put black values into memory...  be careful with your for loops when you start to alter memory
	
	for (int i = 0; i < width * height; i++){
		pixels[i] = 0;
	}
	
	// ---- (5) tell the image to update it's texture from it's pixels so that we can see the change
	
	image.update();
	
}

//--------------------------------------------------------------
void ofApp::update(){
	
	unsigned char * pixels =  image.getPixels();
	
	if (mouseX >= 0 && mouseX < width){
		if (mouseY >= 0 && mouseY < height){
			int pixelPosition = mouseY * width + mouseX;
			pixels[pixelPosition] = 255;
		}
	}
	
	image.update();
}

//--------------------------------------------------------------
void ofApp::draw(){
	
	image.draw(0,0);
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

