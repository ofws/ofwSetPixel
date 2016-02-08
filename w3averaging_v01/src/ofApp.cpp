#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
	
	// set background color to be white: 
	ofBackground(255, 255, 255);
	
	// this prevents banding on mac (vertical sync)
	ofSetVerticalSync(true);
	
	
	// load the image from the data folder
	for (int i = 0; i < 4; i++){
		myPictures[i].loadImage("images/" + ofToString(i) + ".png");
		cout << "images/" + ofToString(i) + ".png" << endl;
		myPictures[i].setImageType(OF_IMAGE_GRAYSCALE);
	}
	
	
	
	// allocate pixels and texture for this image. 
	width = myPictures[0].width;
	height = myPictures[0].height;
	pixelsSum = new int [width * height]; // need to use an int because we are "summing" in
	
	averageImg.allocate(width, height, OF_IMAGE_GRAYSCALE);
	
	unsigned char * pixelsAverage = averageImg.getPixels();
	
	// be sure to initialize the sum we are adding into ! 
	for (int j = 0; j < width * height; j++){
		pixelsSum[j] = 0;
	}
	
	
	for (int i = 0; i < 4; i++){
		unsigned char * pixels = myPictures[i].getPixels();
		for (int j = 0; j < width * height; j++){
			pixelsSum[j] += pixels[j];
		}
	}
	
	for (int j = 0; j < width * height; j++){
		pixelsAverage[j] = pixelsSum[j] / 4;
	}
	
	averageImg.update();
			
}

//--------------------------------------------------------------
void ofApp::update(){
	
	
}

//--------------------------------------------------------------
void ofApp::draw(){
	

	// when we draw, the drawing color "tints" the drawing, so white is best for image
	// ie, white = no tint.
	ofSetColor(255, 255, 255);
	
	averageImg.draw(0, 0);
	
	for (int i = 0; i < 4; i++){
		myPictures[i].draw(i*myPictures[i].width, myPictures[i].height);
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

