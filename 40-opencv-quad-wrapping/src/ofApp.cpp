#include "ofApp.h"

void ofApp::setup(){
	#ifdef _USE_LIVE_VIDEO
        video.setVerbose(true);
        video.initGrabber(320,240);
	#else
        video.load("fingers.mov");
        video.play();
	#endif
    
    width = video.getWidth();
    height = video.getHeight();

    colorImg.allocate(width,height);
	grayImage.allocate(width,height);
	grayBg.allocate(width,height);
	grayDiff.allocate(width,height);
	grayImagePreWarp.allocate(width,height);
	
    srcPts[0].set(0,0);
	srcPts[1].set(width,0);
	srcPts[2].set(width,height);
	srcPts[3].set(0,height);
	
	dstPts[0].set(0,0);
	dstPts[1].set(width,0);
	dstPts[2].set(width,height);
	dstPts[3].set(0,height);
	
	bAdjustingPoint = false;
	whichPointAdjusting = 0;
    
    wrapOffset.set(width*3/4, height/2);
    
    gui.setup();
    gui.add(bLearnBg.setup("learn background ' '", true));
    gui.add(threshold.setup("threshold", 75, 0, 255));
    gui.add(minBlobSize.setup("min blob size", 100, 0, width*height*.2));
    gui.add(maxBlobSize.setup("max blob size", 10000, 0, width*height*.7));
    gui.add(nBlobsConsidered.setup("max blob to find", 3, 0, 20));
    gui.add(framerate.setup("framerate ", ""));
	
    ofSetWindowShape(width*4, height*2);
}

void ofApp::update(){
    
    framerate = ofToString(ofGetFrameRate());
    
    bool bNewFrame = false;
    video.update();
    bNewFrame = video.isFrameNew();

	if (bNewFrame){
        colorImg.setFromPixels(video.getPixels().getData(), width,height);
        grayImagePreWarp = colorImg;
		grayImage.warpIntoMe(grayImagePreWarp, srcPts, dstPts);
		if (bLearnBg){
            // the = sign copys the pixels from grayImage into grayBg (operator overloading)
			grayBg = grayImage;
            bLearnBg = false;
		}

		// take the abs value of the difference between background and incoming and then threshold:
		grayDiff.absDiff(grayBg, grayImage);
		grayDiff.threshold(threshold);

		contourFinder.findContours(grayDiff, minBlobSize, maxBlobSize, nBlobsConsidered, true);
        // find holes
	}

}

void ofApp::draw(){
    ofBackgroundGradient(80, 0);

    ofSetColor(255);
    grayImagePreWarp.draw(wrapOffset);
    grayBg.draw(width*2,0);
	grayImage.draw(width*3,0);
	grayDiff.draw(width*2,height);
	
	// draw wraping rect
    ofPushMatrix();
	ofTranslate(wrapOffset);
	ofBeginShape();
	ofNoFill();
	for (int i = 0; i < 4; i++){
		ofVertex(srcPts[i].x, srcPts[i].y); 
	}
	ofEndShape(true);
	ofFill();
    
    // draw wrapping points
	for (int i = 0; i < 4; i++){
		if (bAdjustingPoint == true && whichPointAdjusting == i) ofSetColor(255, 0, 0);
		else ofSetColor(255);
		ofDrawCircle(srcPts[i].x, srcPts[i].y, 4);
	}
	ofPopMatrix();

    
	// then draw the contours:
	// we could draw the whole contour finder
	//contourFinder.draw(360,540);

	// or, instead we can draw each blob individually,
	// this is how to get access to them:
    for (int i = 0; i < contourFinder.nBlobs; i++){
        contourFinder.blobs[i].draw(width*3,height);
    }

	// finally, a report:
    string s;
    s = "press 1,2,3,4 to adjust warping points";
    s += "\n(any other key to stop adjusting)";
	ofDrawBitmapStringHighlight(s, 20, height*2-30);
    
    gui.draw();
}

void ofApp::keyPressed (int key){
	bAdjustingPoint = false;
	whichPointAdjusting = 0;
	switch (key){
		case ' ':
			bLearnBg = true;
			break;
		case '1':
			bAdjustingPoint = true;
			whichPointAdjusting = 0;
			break;
		case '2':
			bAdjustingPoint = true;
			whichPointAdjusting = 1;
			break;
		case '3':
			bAdjustingPoint = true;
			whichPointAdjusting = 2;
			break;
		case '4':
			bAdjustingPoint = true;
			whichPointAdjusting = 3;
			break;
	}
}


void ofApp::mousePressed(int x, int y, int button){
    for (int i = 0; i < 4; i++){
        if (srcPts[i].distance(ofPoint(x-wrapOffset.x,y-wrapOffset.y)) < 5){
            bAdjustingPoint = true;
            whichPointAdjusting = i;
        }
    }
}

void ofApp::mouseDragged(int x, int y, int button){
    if (bAdjustingPoint){
        srcPts[whichPointAdjusting].set(x-wrapOffset.x, y-wrapOffset.y);
    }
}



