#include "ofApp.h"


bool notFountThisFrame(tracker t){
	return !t.bFoundThisFrame;
}

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
    gui.add(threshold.setup("threshold", 75, 0, 255));
    gui.add(nDilations.setup("nDilations", 2, 0, 20));
    gui.add(nErosions.setup("nErosions", 0, 0, 20));
    gui.add(minBlobSize.setup("minBlobSize", 50, 0, width*height*0.2f));
    gui.add(maxBlobSize.setup("maxBlobSize", 20000, 0, width*height*0.5f));
    gui.add(nBlobsTofind.setup("nBlobs to find", 10, 0, 15));
	
    idCount = 0;
    
    ofSetWindowShape(width*4, height*3);
}

//--------------------------------------------------------------
void ofApp::update(){
		
	int maxOperations		= MAX(nDilations, nErosions);

	video.update();
	
	if (video.isFrameNew()){
		
		videoColorCvImage.setFromPixels(video.getPixels().getData(), width, height);
        videoColorCvImage.mirror(false, true);
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
		
		for (int i = 0; i < maxOperations; i++){
			if (i < nErosions)	videoDiffImage.erode();
			if (i < nDilations)	videoDiffImage.dilate();
		}
		
		contourFinder.findContours(	videoDiffImage, minBlobSize, maxBlobSize, nBlobsTofind,false, true);
		
	}
	
	
	
	// let's track these blobs !
	
	// a) assume all trackers are *not* found this frame.
	for (int i = 0; i < trackerObjects.size(); i++){
		trackerObjects[i].bFoundThisFrame = false;
	}
	
	// b) for all blobs this frame, let's see if we can match them to the trackers.
	int nBlobsFoundThisFrame = contourFinder.nBlobs;
	
	// assume that none have been found:
	bool bAmIFoundThisFrame[nBlobsFoundThisFrame];
	
	if (nBlobsFoundThisFrame > 0){
	
		
		for (int i = 0; i < nBlobsFoundThisFrame; i++){
			bAmIFoundThisFrame[i] = false;
		}
		
		// now, look through every tracker, and see how far away they are from this blob.
		// find the minimum distance, and see if this is reasonable. 
		
		for (int i = 0; i < nBlobsFoundThisFrame; i++){
			
			float	minDistance = 100000;
			int		minIndex	= -1;
			
			for (int j = 0; j < trackerObjects.size(); j++){
				if (trackerObjects[j].bFoundThisFrame == false){
					
					float dx = trackerObjects[j].pos.x - contourFinder.blobs[i].centroid.x;
					float dy = trackerObjects[j].pos.y - contourFinder.blobs[i].centroid.y;
					float distance = sqrt(dx*dx + dy*dy);
					if (distance < minDistance){
						minDistance = distance;
						minIndex = j;
					}
				}
			}
			
			if (minIndex != -1 && minDistance < 100){		// 100 = just a guess.
				trackerObjects[minIndex].pos.x = contourFinder.blobs[i].centroid.x;
				trackerObjects[minIndex].pos.y = contourFinder.blobs[i].centroid.y;
				
				trackerObjects[minIndex].posSmooth.x = 0.99f * trackerObjects[minIndex].posSmooth.x + 
													   0.01f * trackerObjects[minIndex].pos.x;
				trackerObjects[minIndex].posSmooth.y = 0.99f * trackerObjects[minIndex].posSmooth.y + 
													   0.01f * trackerObjects[minIndex].pos.y;
				
				trackerObjects[minIndex].trail.push_back(trackerObjects[minIndex].posSmooth);
				
				trackerObjects[minIndex].whoThisFrame = i;
				trackerObjects[minIndex].bFoundThisFrame = true;
				trackerObjects[minIndex].nFramesActive ++;
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
				temp.posSmooth = temp.pos;
				
				temp.trail.push_back(temp.pos);
			
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
	
	trackerObjects.erase( remove_if(trackerObjects.begin(), trackerObjects.end(), notFountThisFrame), trackerObjects.end() );
	
}

//--------------------------------------------------------------
void ofApp::draw(){
    
    ofBackgroundGradient(80, 0);
    
    ofSetColor(255);
    videoBgImage.draw(0, height);
	videoGrayscaleCvImage.draw(0, height*2);
    
	videoDiffImage.draw(width, 0, width*3, height*3);
	contourFinder.draw(width, 0, width*3, height*3);
	
	/*for (int i = 0; i < contourFinder.nBlobs; i++){
		ofDrawBitmapString("blob id:" + ofToString(i), contourFinder.blobs[i].centroid.x, contourFinder.blobs[i].centroid.y);
	}*/
    
    ofSetColor(ofColor::yellowGreen);
	for (int i = 0; i < trackerObjects.size(); i++){
		int whoAmI = trackerObjects[i].whoThisFrame;
		int id = trackerObjects[i].id;
		ofDrawBitmapString("blob id:" + ofToString(id), (trackerObjects[i].posSmooth.x*3)+width, trackerObjects[i].posSmooth.y*3);
	
		ofNoFill();
		ofBeginShape();
		for (int j = 0; j < trackerObjects[i].trail.size(); j++){
			ofVertex(trackerObjects[i].trail[j].x*3 + width, trackerObjects[i].trail[j].y*3);
		}
		ofEndShape();
	
	}
	gui.draw();
}
