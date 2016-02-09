#include "ofApp.h"

void ofApp::setup(){
    //dynamically load multiple files with array
    for (int i = 0; i < 4; i++){
		myPictures[i].load("images/" + ofToString(i) + ".png");
		cout << "images/" + ofToString(i) + ".png" << endl;
		myPictures[i].setImageType(OF_IMAGE_GRAYSCALE);
	}
	
	// allocate pixels and texture for this image. 
	width = myPictures[0].getWidth();
	height = myPictures[0].getHeight();
	
    // need to use an int because we are "summing" in
    // so it needs to be bigger than char
    pixelsSum = new int [width * height];
    
	// be sure to initialize the sum we are adding into ! 
	for (int j = 0; j < width * height; j++){
		pixelsSum[j] = 0;
	}
	
	for (int i = 0; i < 4; i++){
		unsigned char * pixels = myPictures[i].getPixels().getData();
		for (int j = 0; j < width * height; j++){
			pixelsSum[j] += pixels[j];
		}
	}
    
    // put sum into ofImage & average it
    averageImg.allocate(width, height, OF_IMAGE_GRAYSCALE);
    unsigned char * pixelsAverage = averageImg.getPixels().getData();
    
	for (int j = 0; j < width * height; j++){
		pixelsAverage[j] = pixelsSum[j] / 4;
	}
	averageImg.update();
    ofSetWindowShape(width*2, height*2.5);
}

void ofApp::draw(){
	ofSetColor(255);
	averageImg.draw(0, 0,width*2, height*2);
	
	for (int i = 0; i < 4; i++){
		myPictures[i].draw(i*width/2, height*2, width/2, height/2);
	}
}
