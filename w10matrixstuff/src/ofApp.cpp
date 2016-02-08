#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){

	
	ofBackground(255,255,255);
}

//--------------------------------------------------------------
void ofApp::update(){
	
}

//--------------------------------------------------------------
void ofApp::draw(){
	
	//glTranslatef(<#GLfloat x#>, <#GLfloat y#>, <#GLfloat z#>);
	//glRotatef(<#GLfloat angle#>, <#GLfloat x#>, <#GLfloat y#>, <#GLfloat z#>);
	//glScalef(<#GLfloat x#>, <#GLfloat y#>, <#GLfloat z#>);
	
	
	ofSetColor(0, 0, 0);
	ofRect(10, 10, 100, 100);
	
	
	glPushMatrix();
		
		glTranslatef(200, 0, 0);
		glScalef(2, 1, 0);
		
		ofRect(10, 10, 100, 100);
	
		glPushMatrix();
			glRotatef(PI, 0, 1, 0);
			ofRect(10, 10, 100, 100);
		glPopMatrix();
	
	glPopMatrix();
	
	ofSetColor(255, 0, 0);
	
	ofRect(0, 0, 10, 10);
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

