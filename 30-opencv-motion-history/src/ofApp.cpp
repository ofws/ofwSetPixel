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
	videoDiffMHI.allocate(width, height);
	
    gui.setup();
    gui.add(threshold.setup("threshold", 127, 0, 255));

    ofSetWindowShape(width, height*4);
}

void ofApp::update(){
			
	video.update();
	if (video.isFrameNew()){
		
		videoColorCvImage.setFromPixels(video.getPixels().getData(), width, height);
		videoGrayscaleCvImage = videoColorCvImage;
		
        // compare diffs
		videoDiffImage.absDiff(videoGrayscaleCvImage, videoPrevFrameImage);
		videoDiffImage.threshold(threshold);
		
        // slowly fade out
		videoDiffMHI -= 2;
        // add new diff image
		videoDiffMHI += videoDiffImage;
		videoDiffMHI.blur(9);
        
        //pass current image to prev variable
		videoPrevFrameImage = videoGrayscaleCvImage;
	}
}

void ofApp::draw(){
	
	ofSetColor(255);
	videoGrayscaleCvImage.draw(0,0);
	videoPrevFrameImage.draw(0, height);
	videoDiffImage.draw(0,height*2);
	videoDiffMHI.draw(0, height*3);
	
    gui.draw();
}


