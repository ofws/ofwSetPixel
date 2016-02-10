#include "ofApp.h"

void ofApp::setup(){
	myPicture.load("test.png");
	myPicture.setImageType(OF_IMAGE_GRAYSCALE);
	
	myPictureAsCvImage.allocate(myPicture.getWidth(), myPicture.getHeight());
	myPictureAsCvImage.setFromPixels(myPicture.getPixels().getData(),myPicture.getWidth(), myPicture.getHeight());
	
    gui.setup();
    gui.add(bBlur.setup("blur", false));
    gui.add(blurAmount.setup("blur amount",33, 0,50));
    gui.add(threshold.setup("threshold", 127,0,255));
    
    ofSetWindowShape(myPicture.getWidth(), myPicture.getHeight());
	
}

void ofApp::update(){

	myPictureAsCvImage.setFromPixels(myPicture.getPixels().getData(),myPicture.getWidth(), myPicture.getHeight());
	
	if (bBlur){
        //blur amount should only be odd number
        //there is function that help prevent this
        //but let's save our console some noise
        if(blurAmount%2 == 0) blurAmount = blurAmount + 1;
		myPictureAsCvImage.blur(blurAmount);
	}
	myPictureAsCvImage.threshold(threshold);

}

void ofApp::draw(){
	ofSetColor(255, 255, 255);
	myPictureAsCvImage.draw(0,0);
	gui.draw();
}


