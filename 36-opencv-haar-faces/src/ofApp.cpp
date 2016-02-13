#include "ofApp.h"
void ofApp::setup(){
    ofSetFrameRate(60);
	
    video.setVerbose(true);
	video.initGrabber(320,240);
    width = video.getWidth();
    height = video.getHeight();
    
    colorImg.allocate(width, height);
	grayImage.allocate(width, height);

    gui.setup();
    gui.add(scaleHaar.setup("scale haar", 1.2, 1.05, 3.0));
	
	// load the correct xml file from the bin/data/haarXML/ folder
	haarFinder.setup("haarXML/haarcascade_frontalface_default.xml");
    
    ofSetWindowShape(width*2, height);
}

            
void ofApp::update(){
	haarFinder.setScaleHaar(scaleHaar);
	
	bool bNewFrame = false;
	video.update();
	bNewFrame = video.isFrameNew();

	if (bNewFrame){
		colorImg.setFromPixels(video.getPixels().getData(), 320,240);
        grayImage = colorImg;
		haarFinder.findHaarObjects(grayImage);
	}
}

void ofApp::draw(){

	// draw the incoming & the grayscale
    ofSetColor(255);
    grayImage.draw(0, 0);
	colorImg.draw(width, 0);
	
	// how many matches did you find?
	int numMatches = haarFinder.blobs.size();
	
	// drawing the matches
	ofPushMatrix();
	ofTranslate(width, 0, 0);
	for(int i = 0; i < numMatches; i++){
		float x = haarFinder.blobs[i].boundingRect.x;
		float y = haarFinder.blobs[i].boundingRect.y;
		float w = haarFinder.blobs[i].boundingRect.width;
		float h = haarFinder.blobs[i].boundingRect.height;
		
		float cx = haarFinder.blobs[i].centroid.x;
		float cy = haarFinder.blobs[i].centroid.y;
		
        ofSetColor(ofColor::green);
		ofSetLineWidth(4);
		ofNoFill();
		ofDrawEllipse(x+w/2, y+h/2, w, 4*h/3);

		ofSetColor(255);
		ofDrawBitmapString(ofToString(i), cx, cy);
		
	}
	ofPopMatrix();
	ofSetLineWidth(1);
	
	// drawing some info
    string s;
    s = "matches found: "+ ofToString(numMatches, 0);
    s += "\nframerate: "+ ofToString(ofGetFrameRate(),0);
	ofDrawBitmapStringHighlight(s, 20, height-40);

	gui.draw();
	
}

