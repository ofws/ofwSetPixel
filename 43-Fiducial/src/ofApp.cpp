#include "ofApp.h"


//--------------------------------------------------------------
void ofApp::setup(){	 

	video.setVerbose(true);
	video.initGrabber(320,240);
	colorImg.allocate(320,240);
	grayImage.allocate(320,240);
	grayBg.allocate(320,240);
	grayDiff.allocate(320,240);
	
	threshold = 80;
	bLearnBakground = true;
	backgroundSubOn = false;
	
	//detect finger is off by default
	fidfinder.detectFinger		= true;
	fidfinder.maxFingerSize		= 25; 
	fidfinder.minFingerSize		= 5;
	fidfinder.fingerSensitivity	= 0.05f; //from 0 to 2.0f
}

//--------------------------------------------------------------
void ofApp::update(){
	
	ofBackground(100,100,100);
	video.update();
	
	if (video.isFrameNew()){
		
		colorImg.setFromPixels(video.getPixels().getData(), 320,240);
		grayImage = colorImg;
		
		if (bLearnBakground == true){
			grayBg = grayImage;		// the = sign copys the pixels from grayImage into grayBg (operator overloading)
			bLearnBakground = false;
			backgroundSubOn = true;
		}
		
		// take the abs value of the difference between background and incoming and then threshold:
		if (backgroundSubOn) {
			grayDiff.absDiff( grayBg, grayImage );
		} else {
			grayDiff = grayImage;
		}
		grayDiff.threshold(threshold);
		fidfinder.findFiducials( grayDiff );
	}
	
}

//--------------------------------------------------------------
void ofApp::draw(){
	
	colorImg.draw(20,20);
	grayImage.draw(360,20);
	grayBg.draw(20,280);
	grayDiff.draw(360,280);
	
	//you can use this method for the FidicialFinder
	/*for(int f=0; f<fidfinder._fiducials.size() ;f++) {
		fidfinder._fiducials[f].draw( 20, 20 );
	}*/
	
	//use this method for the FiducialTracker
	//to get fiducial info you can use the fiducial getter methods
	for (list<ofxFiducial>::iterator fiducial = fidfinder.fiducialsList.begin(); fiducial != fidfinder.fiducialsList.end(); fiducial++) {
		fiducial->draw( 20, 20 );//draw fiducial
		fiducial->drawCorners( 20, 20 );//draw corners
		ofSetColor(0,0,255);//set color to blue
		//if mouse (- 20 to compensate for drawing at 20) is inside fiducial then fill
		if (fiducial->isPointInside(mouseX - 20, mouseY - 20)) ofFill();
			else ofNoFill();// else dont
		ofCircle(mouseX, mouseY, 10);//draw mouse position
		ofSetColor(255,255,255);//reset color to white
		//like this one below
		//cout << "fiducial " << fiducial->getId() << " found at ( " << fiducial->getX() << "," << fiducial->getY() << " )" << endl;
		//take a good look at the fiducial class to get all the info and a few helper functions
	 }
	
	//draw the fingers
	for (list<ofxFinger>::iterator finger = fidfinder.fingersList.begin(); finger != fidfinder.fingersList.end(); finger++) {
		finger->draw(20, 20);
	}
	
	printf("fid amount %i\n",fidfinder.fiducialsList.size());
	ofDrawBitmapString( "[space] to learn background\n[+]/[-] to adjust threshold\n[b] to remove background subtraction", 
					   20, 550 );
	
}

//--------------------------------------------------------------
void ofApp::keyPressed  (int key){ 
	if( key == ' ' ) {
        bLearnBakground = true;
    } else if( key == '-' ) {
        threshold = MAX( 0, threshold-1 );
    } else if( key == '+' || key == '=' ) {
        threshold = MIN( 255, threshold+1 );
    } else if( key == 'b' ) {
		backgroundSubOn = false;
	}
}

//--------------------------------------------------------------
void ofApp::keyReleased  (int key){ 
	
}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){
}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){
}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){
}

//--------------------------------------------------------------
void ofApp::mouseReleased(){

}
