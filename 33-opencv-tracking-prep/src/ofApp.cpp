#include "ofApp.h"
void ofApp::setup(){


	//video.loadMovie("file.mp4");
	//video.play();
    
	// setup video grabber:
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
    gui.add(nErosions.setup("nErosions", 0, 0 ,20));
    gui.add(minBlobSize.setup("minBlobSize", 50, 0, width*height*0.2f));
    gui.add(maxBlobSize.setup("maxBlobSize", 20000, 0, width*height*0.5f));
    gui.add(nBlobsTofind.setup("nBlobs to find", 10, 0, 15));
    
    ofSetWindowShape(width*4, height*3);
}

void ofApp::update(){
	int maxOperations = MAX(nDilations, nErosions);
	video.update();
	if (video.isFrameNew()){
		
        videoColorCvImage.setFromPixels(video.getPixels().getData(), width, height);
        videoColorCvImage.mirror(false, true);
		videoGrayscaleCvImage = videoColorCvImage;
		
		if (bLearnBg){
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
		contourFinder.findContours(	videoDiffImage, minBlobSize,maxBlobSize,nBlobsTofind,false, true);
	}
	
}

void ofApp::draw(){
    ofBackgroundGradient(80, 0);
    
    ofSetColor(255);
    videoBgImage.draw(0, height);
	videoGrayscaleCvImage.draw(0,height*2);
    
	videoDiffImage.draw(width,0, width*3, height*3);
	contourFinder.draw(width,0, width*3, height*3);
	
    ofSetColor(ofColor::yellowGreen);
	for (int i = 0; i < contourFinder.nBlobs; i++){
		ofDrawBitmapString("blob id:" + ofToString(i), (contourFinder.blobs[i].centroid.x*3)+width, contourFinder.blobs[i].centroid.y*3);
	}
	gui.draw();
}


