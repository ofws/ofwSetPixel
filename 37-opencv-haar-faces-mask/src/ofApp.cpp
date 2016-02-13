#include "ofApp.h"

bool energyIsLow(tracker t){
	return  ((t.energy < 0.1) && (t.nFramesAlive > 3));
}

void ofApp::setup(){
    
    ofEnableAlphaBlending();
    
	video.setVerbose(true);
	video.initGrabber(320,240);
    
    width = video.getWidth();
    height = video.getHeight();

    colorImg.allocate(width, height);
	grayImage.allocate(width, height);

    gui.setup();
    gui.add(scaleHaar.setup("scale haar", 1.2, 1.04, 3.0));
	
	// load the correct xml file from the bin/data/haarXML/ folder
	haarFinder.setup("haarXML/haarcascade_frontalface_default.xml");

	for (int i = 0; i < 3; i++){
		maskImage[i].load("mask" + ofToString(i) + ".png");
	}
    
    ofSetWindowShape(width*2, height);
}

//--------------------------------------------------------------
void ofApp::update(){
	
	haarFinder.setScaleHaar(scaleHaar);
	
	bool bNewFrame = false;
	video.update();
	bNewFrame = video.isFrameNew();

	if (bNewFrame){
		colorImg.setFromPixels(video.getPixels().getData(), width, height);
        grayImage = colorImg;
		haarFinder.findHaarObjects(grayImage);
	}
	
	// -------------------------------------------------
	
	// let's track these blobs !
	// a) assume all trackers are *not* found this frame.
	for (int i = 0; i < trackerObjects.size(); i++){
		trackerObjects[i].bFoundThisFrame = false;
	}
	
	// b) for all blobs this frame, let's see if we can match them to the trackers.
	int nBlobsFoundThisFrame = haarFinder.blobs.size();
	
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
					float dx = trackerObjects[j].pos.x - haarFinder.blobs[i].centroid.x;
					float dy = trackerObjects[j].pos.y - haarFinder.blobs[i].centroid.y;
					float distance = sqrt(dx*dx + dy*dy);
					if (distance < minDistance){
						minDistance = distance;
						minIndex = j;
					}
				}
			}
			
			if (minIndex != -1 && minDistance < 100){		// 100 = just a guess.
				trackerObjects[minIndex].pos.x = haarFinder.blobs[i].centroid.x;
				trackerObjects[minIndex].pos.y = haarFinder.blobs[i].centroid.y;
				trackerObjects[minIndex].width = haarFinder.blobs[i].boundingRect.width;
				
				trackerObjects[minIndex].widthSmooth = 0.98f * trackerObjects[minIndex].widthSmooth +	
														0.02f * trackerObjects[minIndex].width;
				
				trackerObjects[minIndex].posSmooth.x = 0.9f * trackerObjects[minIndex].posSmooth.x + 
														0.1 * trackerObjects[minIndex].pos.x;
				trackerObjects[minIndex].posSmooth.y = 0.9f * trackerObjects[minIndex].posSmooth.y + 
														0.1 * trackerObjects[minIndex].pos.y;
				
				
				trackerObjects[minIndex].energy += 0.1f;
				if (trackerObjects[minIndex].energy > 1) trackerObjects[minIndex].energy = 1;
				
				trackerObjects[minIndex].whoThisFrame = i;
				trackerObjects[minIndex].bFoundThisFrame = true;
				trackerObjects[minIndex].nFramesAlive ++;
				bAmIFoundThisFrame[i] = true;	// we got one !
			}
		}
	}
	
	// c) for all non found blobs, add a tracker.
	if (nBlobsFoundThisFrame > 0){
		for (int i = 0; i < nBlobsFoundThisFrame; i++){
			if (bAmIFoundThisFrame[i] == false){
				
				tracker temp;
				
				temp.energy = 0;
				
				temp.pos = haarFinder.blobs[i].centroid;
				temp.posSmooth = temp.pos;
				temp.width = haarFinder.blobs[i].boundingRect.width;
				temp.widthSmooth  = temp.width;
				temp.nFramesAlive = 0;
				temp.whoThisFrame = i;
				temp.bFoundThisFrame = true;
				temp.id = idCount;
				trackerObjects.push_back(temp);
				idCount ++;
			}
		}
	}
	
	// d) fade out non found blobs, kill ones that go below a certain value
	// remove_if sorts to the end via a boolean value, 
	// http://en.wikipedia.org/wiki/Erase-remove_idiom
	for (int i = 0; i < trackerObjects.size(); i++){
		if(trackerObjects[i].bFoundThisFrame == false){
			 trackerObjects[i].nFramesAlive++;
			 trackerObjects[i].energy *= 0.95f;	
		}
	}
			 
	trackerObjects.erase( remove_if(trackerObjects.begin(), trackerObjects.end(), energyIsLow), trackerObjects.end() );
	
	
	
}

void ofApp::draw(){

	// draw the incoming & the grayscale
	ofSetColor(255);
    grayImage.draw(0,0);
	colorImg.draw(width,0);
	
	// how many matches did you find?
	int numMatches = haarFinder.blobs.size();
	
	
	ofPushStyle();
	ofSetRectMode(OF_RECTMODE_CENTER);
	
	// drawing the matches
	ofPushMatrix();
	ofTranslate(width, 0, 0);
	for(int i = 0; i < trackerObjects.size(); i++){
		
		
		float cx = trackerObjects[i].posSmooth.x;
		float cy = trackerObjects[i].posSmooth.y;
		
		ofSetColor(255, trackerObjects[i].energy * 255);
		
		float width = trackerObjects[i].width;
		
		
		maskImage[CLAMP(trackerObjects[i].id % 3,0,2)].draw(cx,cy,width,width);
	}
	ofPopMatrix();
	ofPopStyle();
	
	gui.draw();
	
}

