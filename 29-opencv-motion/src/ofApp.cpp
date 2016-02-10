#include "ofApp.h"

void ofApp::setup(){
	// setup video grabber:
	video.initGrabber(320, 240);
    
	// get the width and height, and allocate color and grayscale images:
	width = video.getWidth();
	height = video.getHeight();
	
	videoColorCvImage.allocate(width, height);
	videoGrayscaleCvImage.allocate(width, height);
	videoPrevFrameImage.allocate(width, height);
	videoDiffImage.allocate(width, height);
	
    gui.setup();
    gui.add(threshold.setup("threshold", 127,0,255));
    
    ofSetWindowShape(width*2, height*3);
}

void ofApp::update(){
	video.update();
	if (video.isFrameNew()){
		
		videoColorCvImage.setFromPixels(video.getPixels().getData(), width, height);
		videoGrayscaleCvImage = videoColorCvImage;
		
		videoDiffImage.absDiff(videoGrayscaleCvImage, videoPrevFrameImage);
		videoDiffImage.threshold(threshold);
		
		videoPrevFrameImage = videoGrayscaleCvImage;
	}
}

void ofApp::draw(){
	ofSetColor(255);
	videoGrayscaleCvImage.draw(0,0,width,height);
	videoPrevFrameImage.draw(width, 0, width, height);
	videoDiffImage.draw(0,height, width*2, height*2);
	gui.draw();
}
