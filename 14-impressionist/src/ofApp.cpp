#include "ofApp.h"

void ofApp::setup(){
	camWidth 	= 80;
	camHeight 	= 60;
	
	vidGrabber.setVerbose(true);
	vidGrabber.initGrabber(camWidth,camHeight);
	
	ofSetVerticalSync(true);
	
	ofBackground(0);
	
	//this application attempts to find pixels of a similar color around each pixel in the image.
    //if it finds any, it draws a line of the original pixels color to the similar pixel
	
	// messing with these two can generate really different stuff,
    // although it can also make the program run really slowly
    
    // threshold for agreeing that a pixel is a similar color
	comparisonThreshold = 3;
    // distance to check away from starting pixel
	comparisonDistance = 12;
}

void ofApp::update(){
	vidGrabber.update();
    ofSetWindowTitle(ofToString(ofGetFrameRate()));
}

void ofApp::draw(){
	
	ofSetLineWidth(10);
    unsigned char * pixels = vidGrabber.getPixels().getData();
	
	int gridSquareWidth = ofGetWidth()/camWidth;
	int gridSquareHeight = ofGetHeight()/camHeight;
	
	for(int x=0; x<camWidth; x++){
		for(int y=0; y<camHeight; y++){
			int colorIndex = (y * camWidth + x) * 3;
            // add all the chanels together
			int colorAvg = pixels[colorIndex] + pixels[colorIndex + 1] + pixels[colorIndex + 2];
			//and divide by 3
            colorAvg /= 3;
			
			int r = 0;
			
			// look through all the pixels around my pixel in a square,
            // use MIN() and MAX() to make sure we don't accidentally try and access a pixel outside of the image
			for(int x2 = MAX(x-comparisonDistance, 0); x2 < MIN(x+comparisonDistance, camWidth); x2++){
				for(int y2 = MAX(y-comparisonDistance, 0); y2 < MIN(y+comparisonDistance, camHeight); y2++){
                    
                    //if we're not looking at our original pixel
					if(x2 != x && y2 != y){
						int newColorIndex = (y2 * camWidth + x2) * 3;
                        // add all the chanels together
						int newColorAvg = pixels[newColorIndex] + pixels[newColorIndex + 1] + pixels[newColorIndex + 2];
						// and divide by 3
                        newColorAvg /= 3;

                        // if the colors are similar enough
                        // draw a line between them and the original pixels color
						if(ABS(colorAvg - newColorAvg) < comparisonThreshold){
							ofSetColor(pixels[colorIndex + 0],
                                       pixels[colorIndex + 1],
                                       pixels[colorIndex + 2]);
                            
							// get a random number between -10 and 10 to add to our line points to make things move a bit
							r = ofRandomf()*10;
							
							//actually draw the line
							ofDrawLine(x*gridSquareWidth + r,
                                       y*gridSquareHeight + r,
                                       x2*gridSquareWidth + r,
                                       y2*gridSquareHeight + r);
						}
					}
				}
			}
		}
	}
}
