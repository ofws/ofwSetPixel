#include "testApp.h"

//--------------------------------------------------------------
void testApp::setup(){

	// setup video grabber:
	video.initGrabber(320, 240);
	
	// get the width and height, and allocate color and grayscale images: 
	width = video.width; 
	height = video.height;
	
	videoColorCvImage.allocate(width, height);
	videoGrayscaleCvImage.allocate(width, height);
	videoBgImage.allocate(width, height);
	videoDiffImage.allocate(width, height);
	
	// set background color to be white: 
	ofBackground(255, 255, 255);
	
	
	panel.setup("cv settings", 720, 0, 300, 748);
	panel.addPanel("control", 1, false);
	
	panel.setWhichPanel("control");
	panel.addToggle("learn background ", "B_LEARN_BG", true);
	panel.addSlider("threshold ", "THRESHOLD", 127, 0, 255, true);
	
	panel.loadSettings("cvSettings.xml");
	
	for (int i = 0; i < 1000; i++){
		particle temp;
		temp.setup();
		particles.push_back(temp);
	}
	
	bDrawDebug = true;
	
	ofSetVerticalSync(true);
}

//--------------------------------------------------------------
void testApp::update(){
	
	for (int i = 0; i < particles.size(); i++){
		particles[i].checkImage(&videoDiffImage);
		particles[i].update();
	}
	
	
	panel.update();
	
	
	bool bLearnBg			= panel.getValueB("B_LEARN_BG");
	int threshold			= panel.getValueI("THRESHOLD");

	
	video.update();
	
	if (video.isFrameNew()){
		
		videoColorCvImage.setFromPixels(video.getPixels(), width, height);
		videoGrayscaleCvImage = videoColorCvImage;
		
		if (bLearnBg ){ 
			videoBgImage = videoGrayscaleCvImage;
			panel.setValueB("B_LEARN_BG", false);
		}
		
		if (ofGetElapsedTimef() < 1.5){
			videoBgImage = videoGrayscaleCvImage;
		}
		
		videoDiffImage.absDiff(videoGrayscaleCvImage, videoBgImage);
		videoDiffImage.threshold(threshold);
		
							
								
	}
	
}

//--------------------------------------------------------------
void testApp::draw(){
	
	if (bDrawDebug){
		ofSetColor(255, 255, 255);
		videoGrayscaleCvImage.draw(20,20, 320,240);
		videoBgImage.draw(320+40, 20, 320, 240);
		videoDiffImage.draw(20,240+40);
		panel.draw();
		
		ofSetColor(0, 0, 0);
		ofDrawBitmapString("press space ' ' to toggle", 20, 610);
	} else {
		for (int i = 0; i < particles.size(); i++){
			particles[i].draw();
		}
	}
}

//--------------------------------------------------------------
void testApp::keyPressed(int key){

	if (key == ' '){
		bDrawDebug =!bDrawDebug;
	}
}

//--------------------------------------------------------------
void testApp::keyReleased(int key){

}

//--------------------------------------------------------------
void testApp::mouseMoved(int x, int y ){
	
}

//--------------------------------------------------------------
void testApp::mouseDragged(int x, int y, int button){
	panel.mouseDragged(x,y,button);
}

//--------------------------------------------------------------
void testApp::mousePressed(int x, int y, int button){
	panel.mousePressed(x,y,button);
}

//--------------------------------------------------------------
void testApp::mouseReleased(int x, int y, int button){
	panel.mouseReleased();
}

//--------------------------------------------------------------
void testApp::windowResized(int w, int h){

}

