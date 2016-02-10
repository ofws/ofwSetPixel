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
    gui.add(threshold.setup("threshold", 75, 0, 255));
    gui.add(bUseBlur.setup("use blur", false));
    gui.add(blurAmount.setup("blur amount", 11, 0, 30));
    gui.add(minBlobSize.setup("min blob size", 100, 0, width*height));
    gui.add(maxBlobSize.setup("max blob size", 10000, 0, width*height));
    gui.add(nBlobsConsidered.setup("max num blobs to find", 3, 0, 20));
 	
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
        if (bUseBlur) {
            if (blurAmount %2 == 0) blurAmount = blurAmount + 1;
            videoDiffImage.blur(blurAmount);
        }
		videoDiffImage.threshold(threshold);
		contourFinder.findContours(videoDiffImage, minBlobSize, maxBlobSize, nBlobsConsidered, false, true);

		ofLog() << "we found " << contourFinder.nBlobs << " blobs";
		for (int i = 0; i <  contourFinder.nBlobs; i++){
			ofLog() << "centroid of blob " <<  i << "=" << contourFinder.blobs[i].centroid.x << "," << contourFinder.blobs[i].centroid.y;
		}
	}
}

void ofApp::draw(){
	
	ofSetColor(255);
    videoBgImage.draw(0, 0);
	videoGrayscaleCvImage.draw(0,height);
	videoDiffImage.draw(0,height*2);
	contourFinder.draw(0,height*2);
	gui.draw();
}
