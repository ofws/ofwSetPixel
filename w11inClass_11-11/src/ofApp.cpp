#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
	
	ofSetFrameRate(60);
	ofSetVerticalSync(true);
	
	for (int i = 0; i < NUM_CIRCLES; i++) {
		
		circles[i].setup();
		
		
	}
	
	
}

//--------------------------------------------------------------
void ofApp::update(){
	
	for (int i = 0; i < NUM_CIRCLES; i++) {
		
		if (i ==0) {
			
			circles[i].update(circles[NUM_CIRCLES -1]);
			
		}
		
		for (int j = 0; j < i; j++) {
		
			circles[i].update( circles[j] );
		}
		
	}

}

//--------------------------------------------------------------
void ofApp::draw(){
	ofBackground(40, 40, 40);

	for (int i = 0; i < NUM_CIRCLES; i++) {
		
		//modulus operator
//		if( i % 7 == 0) {
//			ofFill();
//		} else {
//			ofNoFill();
//		}
		
		ofFill();
		circles[i].draw();
		
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

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){ 

}