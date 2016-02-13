#include "ofApp.h"

void ofApp::setup(){
	video.initGrabber(320, 240);
	width = video.getWidth();
	height = video.getHeight();
	
	videoColorCvImage.allocate(width, height);
	videoGrayscaleCvImage.allocate(width, height);
	videoBlurImage.allocate(width, height);
	videoDiffImage.allocate(width, height);
	
    gui.setup();
    gui.add(threshold.setup("threshold", 10, 0, 255));
    gui.add(blur.setup("num blurs", 10, 1, 100));
	
    ofSetWindowShape(width, height*3);
}

void ofApp::update(){
	video.update();
	
	if (video.isFrameNew()){
		
		videoColorCvImage.setFromPixels(video.getPixels().getData(), width, height);
		videoGrayscaleCvImage = videoColorCvImage;
		videoBlurImage = videoGrayscaleCvImage;
		for (int i = 0; i < blur; i++){
			videoBlurImage.blur(3);
		}
		
		videoDiffImage.absDiff(videoGrayscaleCvImage, videoBlurImage);
		videoDiffImage.threshold(threshold);
	}
	
}

void ofApp::draw(){
	
	ofSetColor(255);
	videoGrayscaleCvImage.draw(0,0);
	videoBlurImage.draw(0, height);
	videoDiffImage.draw(0, height*2);
	gui.draw();
}
