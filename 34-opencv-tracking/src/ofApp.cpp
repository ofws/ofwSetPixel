#include "ofApp.h"


bool notFoundThisFrame(tracker t){
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

void ofApp::update(){
	int maxOperations = MAX(nDilations, nErosions);
    
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
			if (i < nDilations)	videoDiffImage.dilate();
			if (i < nErosions)	videoDiffImage.erode();
		}
		
		contourFinder.findContours(videoDiffImage, minBlobSize, maxBlobSize, nBlobsTofind, false, true);
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

void ofApp::draw(){
    ofBackgroundGradient(80, 0);
    
    ofSetColor(255);
    videoBgImage.draw(0, height);
	videoGrayscaleCvImage.draw(0, height*2);
	videoDiffImage.draw(width,0, width*3,height*3);
	
	contourFinder.draw(width,0, width*3,height*3);

//	for (int i = 0; i < contourFinder.nBlobs; i++){
//		ofDrawBitmapString("blob id:" + ofToString(i), contourFinder.blobs[i].centroid.x, contourFinder.blobs[i].centroid.y);
//	}
	
    ofSetColor(ofColor::yellowGreen);
	for (int i = 0; i < trackerObjects.size(); i++){
		int whoAmI = trackerObjects[i].whoThisFrame;
		int id = trackerObjects[i].id;
		ofDrawBitmapString("blob id:" + ofToString(id), (contourFinder.blobs[whoAmI].centroid.x*3)+width, contourFinder.blobs[whoAmI].centroid.y*3);
	}
	gui.draw();
}

