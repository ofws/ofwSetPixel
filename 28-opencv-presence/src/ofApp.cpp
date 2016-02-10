#include "ofApp.h"
void ofApp::setup(){
    
	video.initGrabber(320, 240);
	
	width = video.getWidth();
	height = video.getHeight();
	
	videoColorCvImage.allocate(width, height);
	videoGrayscaleCvImage.allocate(width, height);
	videoBgImage.allocate(width, height);
	videoDiffImage.allocate(width, height);
	
    gui.setup();
    gui.add(bLearnBg.setup("learn background", true));
    gui.add(threshold.setup("threshold", 70, 0 , 255));
    
    ofSetWindowShape(width, height*3);

}
void ofApp::update(){
	video.update();
	if (video.isFrameNew()){
		videoColorCvImage.setFromPixels(video.getPixels().getData(), width, height);
		videoGrayscaleCvImage = videoColorCvImage;
		
		if (bLearnBg ){ 
			videoBgImage = videoGrayscaleCvImage;
            bLearnBg = false;
		}
		
		if (ofGetElapsedTimef() < 1.5){
			videoBgImage = videoGrayscaleCvImage;
		}
        
		videoDiffImage.absDiff(videoGrayscaleCvImage, videoBgImage);
		videoDiffImage.threshold(threshold);
	}
}
void ofApp::draw(){
	ofSetColor(255);
    
    videoBgImage.draw(0, 0);
	videoGrayscaleCvImage.draw(0,height);
	videoDiffImage.draw(0,height*2);
    
	gui.draw();
}
