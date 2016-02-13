#include "ofApp.h"


//--------------------------------------------------------------
void ofApp::setup(){	 

	vidGrabber.setVerbose(true);
	vidGrabber.initGrabber(320,240);
	colorImg.allocate(320,240);
	grayImage.allocate(320,240);
	
	threshold = 80;
	
}

//--------------------------------------------------------------
void ofApp::update(){
	
	ofBackground(100,100,100);
	vidGrabber.update();
	
	if (vidGrabber.isFrameNew()){
		
		colorImg.setFromPixels(vidGrabber.getPixels(), 320,240);
		grayImage = colorImg;

		grayImage.threshold(threshold);
		fidfinder.findFiducials( grayImage );
	}
	
}

//--------------------------------------------------------------
void ofApp::draw(){
	
	colorImg.draw(20,20);
	grayImage.draw(360,20);
	
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
		ofDrawBitmapString("angle: "+ofToString(fiducial->getAngleDeg()), fiducial->getX()+20, fiducial->getY()+20);
		//like this one below
		//cout << "fiducial " << fiducial->getId() << " found at ( " << fiducial->getX() << "," << fiducial->getY() << " )" << endl;
		//take a good look at the fiducial class to get all the info and a few helper functions
		
		/*
		if(fiducial->getId() == 0)
			ofRect(fiducial->getX()+20, fiducial->getY()+20, 10, 10);
		else if(fiducial->getId() == 1)
			//do something else*/
	}
	printf("fid amount %i\n",fidfinder.fiducialsList.size());
	ofDrawBitmapString( "[+]/[-] to adjust threshold", 
					   20, 550 );
	
}

//--------------------------------------------------------------
void ofApp::keyPressed  (int key){ 
	if( key == '-' ) {
        threshold = MAX( 0, threshold-1 );
    } else if( key == '+' || key == '=' ) {
        threshold = MIN( 255, threshold+1 );
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
