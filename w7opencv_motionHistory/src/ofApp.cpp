#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){

	// setup video grabber:
	video.initGrabber(320, 240);
	//video.videoSettings();
	// get the width and height, and allocate color and grayscale images: 
	width = video.width; 
	height = video.height;
	
	videoColorCvImage.allocate(width, height);
	videoGrayscaleCvImage.allocate(width, height);
	
	videoPrevFrameImage.allocate(width, height);
	videoDiffImage.allocate(width, height);
	
	videoDiffMHI.allocate(width, height);
	
	// set background color to be white: 
	ofBackground(255, 255, 255);
	
	
	panel.setup("cv settings", 720, 0, 300, 748);
	panel.addPanel("control", 1, false);
	
	panel.setWhichPanel("control");
	panel.addSlider("threshold ", "THRESHOLD", 127, 0, 255, true);
	
	panel.loadSettings("cvSettings.xml");
}

//--------------------------------------------------------------
void ofApp::update(){
		
	panel.update();
	
	
	int threshold			= panel.getValueI("THRESHOLD");

	
	video.update();
	
	if (video.isFrameNew()){
		
		videoColorCvImage.setFromPixels(video.getPixels(), width, height);
		videoGrayscaleCvImage = videoColorCvImage;
		
		
		
		videoDiffImage.absDiff(videoGrayscaleCvImage, videoPrevFrameImage);
		videoDiffImage.threshold(threshold);
		
		videoDiffMHI -= 2;
		videoDiffMHI += videoDiffImage;
		videoDiffMHI.blur(9);
		 
		
		
		videoPrevFrameImage = videoGrayscaleCvImage;
							
								
	}
	
}

//--------------------------------------------------------------
void ofApp::draw(){
	
	ofSetColor(255, 255, 255);
	videoGrayscaleCvImage.draw(20,20, 320,240);
	videoPrevFrameImage.draw(320+40, 20, 320, 240);
	videoDiffImage.draw(20,240+40);
	videoDiffMHI.draw(320+40, 240+40);
	panel.draw();
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
	panel.mouseDragged(x,y,button);
}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){
	panel.mousePressed(x,y,button);
}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){
	panel.mouseReleased();
}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h){

}

