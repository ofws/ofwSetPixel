#include "ofApp.h"

void ofApp::setup(){
	myPicture.load("test.png");
	myPicture.setImageType(OF_IMAGE_GRAYSCALE);
    ofSetWindowShape(myPicture.getWidth()*2, myPicture.getHeight()+30);
}
void ofApp::draw(){
	
    ofBackgroundGradient(ofColor(80), ofColor(0));
	ofSetColor(255);
	myPicture.draw(0,0);
	
	unsigned char * pixelsFromImage = myPicture.getPixels().getData();
	int width = myPicture.getWidth();
	int height = myPicture.getHeight();
	
	// copy the pixels in and upload
	for (int x = 0; x < width; x+=20){
		for (int y = 0; y < height; y+=20){
			
			int pixIndex = y * width + x;
			int pixVal = pixelsFromImage[pixIndex];
			float pct = (float)pixVal / 255.0f;
			ofDrawCircle(width + 10 + x, y, 10*pct);
		}
	}
	ofDrawBitmapString("press space to save to postscript", 20, height + 20);
}

void ofApp::keyPressed(int key){

	if (key == ' '){
		
		ofLog() << "saving out to file...";
		// let's save out some data!
        // filename and x, y, w, h of boundingbox
		output.beginEPS("test.ps",0,0,myPicture.getWidth(),myPicture.getHeight());
		
		unsigned char * pixelsFromImage = myPicture.getPixels().getData();
		int width = myPicture.getWidth();
		int height = myPicture.getHeight();
		
        // black background
		output.setColor(0);
		output.rect(0,0,width, height);
		
        // white circles
		output.setColor(255,255,255);
		for (int i = 0; i < width; i+=20){
			for (int j = 0; j < height; j+=20){
				int pixIndex = j * width + i;
				int pixVal = pixelsFromImage[pixIndex];
				float pct = (float)pixVal / 255.0f;
				output.circle(10 + i, j, 10 * (pct));
			}
		}
		output.endEPS();
	}
}
