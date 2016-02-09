#include "ofApp.h"

void ofApp::setup(){
    // try to grab at this size.
    // it's so small because we dont need that much information since we're messing with the image
    //instead of skipping pixels later, im just starting with a smaller image

	camWidth 	= 48;
	camHeight 	= 36;
    
    vidGrabber.setVerbose(true);
	vidGrabber.initGrabber(camWidth,camHeight);
	
	ofSetVerticalSync(true);
}

void ofApp::update(){
	vidGrabber.update();
}

void ofApp::draw(){
    ofBackgroundGradient(ofColor(40), ofColor(0));
  
    // the width of each square..
    // basically we're dividing the whole screen by the number of pixels in our webcam grab
	int gridSquareWidth = ofGetWidth()/camWidth;
    // we need to know what a 3rd of the width of each square is also,
    // since we'll be drawing 3 graph bars in each sq, one for each channel
    int gridSquareWidthThird = gridSquareWidth/3;
	int gridSquareHeight = ofGetHeight()/camHeight;
	
    // get the pixels from the camera
	unsigned char * pixels = vidGrabber.getPixels().getData();
	
	for(int x=0; x<camWidth; x++){
		for(int y=0; y<camHeight; y++){
            
            // normal y*width+x, except because there are 3 channels per each color
            // so we have to multiply the whole thing by 3
			int colorIndex = (y * camWidth + x) * 3;
			int mappedValue;
            
			// go through each channel
            for(int c = 0; c<3; c++){
                // map the value of each channel from 0-255 into 0 to the height of each grid spare
				mappedValue = ofMap(pixels[colorIndex + c], 0, 255, 0, gridSquareHeight);
				
                // figure out which channel we're looking at,
                // and then set the color to just the strength of that channel
                if (c==0){
					ofSetColor(pixels[colorIndex + 0], 0, 0);
                }
                else if (c==1){
					ofSetColor(0, pixels[colorIndex + 1], 0);
                }
                else {
					ofSetColor(0, 0, pixels[colorIndex + 2]);
                }
                
				//draw a rectangle in the right place
				ofDrawRectangle(x*gridSquareWidth + gridSquareWidthThird*c,
                                y*gridSquareHeight + gridSquareHeight,
                                gridSquareWidthThird,
                                -mappedValue);
			}
		}
	}
}