#include "ofApp.h"


bool notFoundThisFrame(tracker t){
	return !t.bFoundThisFrame;
}

//--------------------------------------------------------------
void ofApp::setup(){

	// setup video grabber:
	//video.loadMovie("Swarm_EindhovenTest_Watec_heavy-occlusion.mov");
	//video.play();
	
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
	panel.setWhichColumn(0);
	panel.addToggle("learn background ", "B_LEARN_BG", true);
	panel.addSlider("threshold ", "THRESHOLD", 127, 0, 255, true);
	
	panel.addSlider("nDilations ", "N_DILATIONS", 2, 0, 20, true);
	panel.addSlider("nErosions ", "N_EROSION", 0, 0, 20, true);
	
	panel.addSlider("minBlobSize ", "MIN_BLOB_SIZE", 50, 0, width*height*0.2f, true);
	panel.addSlider("maxBlobSize ", "MAX_BLOB_SIZE", 20000, 0, width*height*0.5f, true);
	panel.addSlider("nBlobs to find ", "N_BLOBS_TO_FIND", 10, 0, 15, true);
	
	panel.loadSettings("cvSettings.xml");
	
	idCount = 0;
}

//--------------------------------------------------------------
void ofApp::update(){
		
	panel.update();
	
	
	bool bLearnBg			= panel.getValueB("B_LEARN_BG");
	int threshold			= panel.getValueI("THRESHOLD");
	int nDilations			= panel.getValueI("N_DILATIONS");
	int nErosions			= panel.getValueI("N_EROSION");
	int maxOperations		= MAX(nDilations, nErosions);
	int minBlobSize			= panel.getValueI("MIN_BLOB_SIZE");
	int maxBlobSize			= panel.getValueI("MAX_BLOB_SIZE");
	int bBlobsTofind		= panel.getValueI("N_BLOBS_TO_FIND");

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
		
		for (int i = 0; i < maxOperations; i++){
			
			if (i < nDilations)	videoDiffImage.dilate();
			if (i < nErosions)	videoDiffImage.erode();
		}
		
		contourFinder.findContours(	videoDiffImage, minBlobSize,maxBlobSize,bBlobsTofind,false, true);
		
	}
	
	
	
	// let's track these blobs !
	
	// a) assume all trackers are *not* found this frame. 
	
	for (int i = 0; i < trackerObjects.size(); i++){
		trackerObjects[i].bFoundThisFrame = false;
	}
	
	// b) for all blobs this frame, let's see if we can match them to the trackers.  
	
	int nBlobsFoundThisFrame = contourFinder.nBlobs;
	
	// create an array for the blob found status
	bool bAmIFoundThisFrame[nBlobsFoundThisFrame];
	
	if (nBlobsFoundThisFrame > 0){ // if there are blobs
	
		//assume that none have been found:
		for (int i = 0; i < nBlobsFoundThisFrame; i++){
			bAmIFoundThisFrame[i] = false;
		}
		
		// now, look through every tracker, and see how far away they are from this blob.
		// find the minimum distance, and see if this is reasonable. 
		
		for (int i = 0; i < nBlobsFoundThisFrame; i++){
			
			float	minDistance = 100000;
			int		closestBlobIndex	= -1;
			
			for (int j = 0; j < trackerObjects.size(); j++){
				if (trackerObjects[j].bFoundThisFrame == false){
					
					float dx = trackerObjects[j].pos.x - contourFinder.blobs[i].centroid.x;
					float dy = trackerObjects[j].pos.y - contourFinder.blobs[i].centroid.y;
					float distance = sqrt(dx*dx + dy*dy);
					
					//or you could use ofDist()
					
					if (distance < minDistance){
						minDistance = distance;
						closestBlobIndex = j;
					}
				}
			}
			
			if (closestBlobIndex != -1 && minDistance < 100){		// 100 = just a guess.
				trackerObjects[closestBlobIndex].pos.x = contourFinder.blobs[i].centroid.x;
				trackerObjects[closestBlobIndex].pos.y = contourFinder.blobs[i].centroid.y;
				trackerObjects[closestBlobIndex].whoThisFrame = i;
				trackerObjects[closestBlobIndex].bFoundThisFrame = true;
				trackerObjects[closestBlobIndex].nFramesActive ++;
				bAmIFoundThisFrame[i] = true;	// we got one !
			}
		}
	}
	
	// c) for all non found blobs, add a tracker. 
	
	if (nBlobsFoundThisFrame > 0){
		for (int i = 0; i < nBlobsFoundThisFrame; i++){
			if (bAmIFoundThisFrame[i] == false){
				
				tracker temp;
				temp.pos = contourFinder.blobs[i].centroid;
				temp.nFramesActive = 0;
				temp.whoThisFrame = i;
				temp.bFoundThisFrame = true;
				temp.id = idCount;
				trackerObjects.push_back(temp);
				idCount ++;
			}
		}
	}
	
	// d) kill all trackers that haven't been found
	// remove_if sorts to the end via a boolean value, 
	// http://en.wikipedia.org/wiki/Erase-remove_idiom
	
	trackerObjects.erase( remove_if(trackerObjects.begin(), trackerObjects.end(), notFoundThisFrame), trackerObjects.end() );
	
}

//--------------------------------------------------------------
void ofApp::draw(){
	
	ofSetColor(255, 255, 255);
	videoGrayscaleCvImage.draw(20,20, 320,240);
	videoBgImage.draw(320+40, 20, 320, 240);
	videoDiffImage.draw(20,240+40, 640,480);
	
	contourFinder.draw(20,240+40,640,480);
	
	/*for (int i = 0; i < contourFinder.nBlobs; i++){
		ofDrawBitmapString("blob id:" + ofToString(i), contourFinder.blobs[i].centroid.x, contourFinder.blobs[i].centroid.y);
	}*/
	
	for (int i = 0; i < trackerObjects.size(); i++){
		int whoAmI = trackerObjects[i].whoThisFrame;
		int id = trackerObjects[i].id;
		ofDrawBitmapString("blob id:" + ofToString(id), contourFinder.blobs[whoAmI].centroid.x, contourFinder.blobs[whoAmI].centroid.y);
	}
	
	
	panel.draw();

}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
	if(key=='s')
		video.videoSettings();
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
