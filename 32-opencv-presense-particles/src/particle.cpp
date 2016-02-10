#include "particle.h"


void particle::setup(){
	pos.x = ofRandom(0,ofGetWidth());
	pos.y = ofRandom(0,ofGetHeight());
	energy = 1;
}

void particle::update(){
	if (energy < 1) energy += 0.01;
}

void particle::checkImage( ofxCvGrayscaleImage * myImage){
	
	float pctx = pos.x / (float)ofGetWidth();
	pctx = ofClamp(pctx, 0,1);
	float pcty = pos.y / (float)ofGetHeight();
	pcty = ofClamp(pcty, 0,1);
	
	int pixXinImage = myImage->width * pctx;
	int pixYinImage = myImage->height * pcty;
	
	unsigned char * pixels = myImage->getPixels().getData();
	if (pixels[pixYinImage * myImage->width + pixXinImage] > 127){
		energy = 0;
	}
}

void particle::draw(){
	ofSetColor(255,50);
	ofDrawCircle(pos.x, pos.y, ofGetHeight()*.05 * energy);
}
