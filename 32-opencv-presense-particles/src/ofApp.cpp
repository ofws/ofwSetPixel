#include "ofApp.h"

void ofApp::setup(){

    ofEnableAlphaBlending();
    ofSetVerticalSync(true);

	video.initGrabber(320, 240);
	width = video.getWidth();
	height = video.getHeight();
	
	videoColorCvImage.allocate(width, height);
	videoGrayscaleCvImage.allocate(width, height);
	videoBgImage.allocate(width, height);
	videoDiffImage.allocate(width, height);
	
    gui.setup();
    gui.add(bLearnBg.setup("learn background (b)", true));
    gui.add(threshold.setup("threshold", 75, 0, 255));
    gui.add(bDrawDebug.setup("draw debug mode (space)", false));
    gui.add(bDrawGui.setup("draw gui (h)", true));
	
	
	for (int i = 0; i < 1000; i++){
		particle temp;
		temp.setup();
		particles.push_back(temp);
	}
    
    ofSetWindowShape(width*2, height*2);
}

void ofApp::update(){


	
    video.update();
	
	if (video.isFrameNew()){
		
		videoColorCvImage.setFromPixels(video.getPixels().getData(), width, height);
        // mirror so it feels more natural to interact with
        videoColorCvImage.mirror(false, true);
		videoGrayscaleCvImage = videoColorCvImage;
		
		if (bLearnBg){
			videoBgImage = videoGrayscaleCvImage;
            bLearnBg = false;
		}
		
        //make sure this happens during the first second the app runs
		if (ofGetElapsedTimef() < 1.5){
			videoBgImage = videoGrayscaleCvImage;
		}
		
		videoDiffImage.absDiff(videoGrayscaleCvImage, videoBgImage);
		videoDiffImage.threshold(threshold);
								
	}
    
    // particle - check with diff image
    for (int i = 0; i < particles.size(); i++){
        particles[i].checkImage(&videoDiffImage);
        particles[i].update();
    }
    
    // allow a few frames to grab the right screen width/height
    if (pResetCounter < 5) {
        for (auto& p:particles) {
            p.setup();
        }
    }
    pResetCounter++;
}

void ofApp::draw(){
    ofBackgroundGradient(80, 0);
	
	if (bDrawDebug){
		ofSetColor(255);
        videoBgImage.draw(0, height);
		videoGrayscaleCvImage.draw(width, height);
		videoDiffImage.draw(width, 0);
	} else {
		for (int i = 0; i < particles.size(); i++){
			particles[i].draw();
		}
	}
    
    if (bDrawGui) {
        gui.draw();
        string s;
        s = "press space ' ' to toggle mode\n";
        s += "press 'h' to toggle gui\n";
        s += "press 'f' to toggle fullscreen\n";
        s += "press 'b' to learn background";
        ofDrawBitmapStringHighlight(s, 20, ofGetHeight()-70);
    }
}

void ofApp::keyPressed(int key){
	if (key == ' ') bDrawDebug =!bDrawDebug;
    if (key == 'h') bDrawGui = !bDrawGui;
    if (key == 'b') bLearnBg = true;
    if (key == 'f') {
        ofToggleFullscreen();
        pResetCounter = 0;
    }
}
