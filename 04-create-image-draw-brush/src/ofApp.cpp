#include "ofApp.h"
void ofApp::setup(){
	ofSetVerticalSync(true);

	width = 500;
	height = 500;
	image.allocate(width, height, OF_IMAGE_GRAYSCALE);
	
	unsigned char * pixels =  image.getPixels().getData();
	for (int i = 0; i < width * height; i++){
		pixels[i] = 0;
	}
	image.update();
    ofSetWindowShape(width, height);
}

void ofApp::update(){
	unsigned char * pixels =  image.getPixels().getData();
	// find points that are within a certain distance of the mouse:
	// note this is SLOW ;)
	for (int i = 0; i < width; i++){
		for (int j = 0; j < height; j++){
			int diffx = (i - mouseX);
			int diffy = (j - mouseY);
			float distance = sqrt(diffx*diffx + diffy*diffy);
            float rad = 30;
			if (distance < rad){
				//pixels[j * width + i] = 255;
				//	percentage based stuff to show in class. 
				float pct = distance / (float)rad;
				pixels[j * width + i] = MIN(255, pixels[j * width + i] + 255 * (1-pct));
			}
		}
	}
	
	// fade routine.
	 for (int i = 0; i < width; i++){
		 for (int j = 0; j < height; j++){
			 pixels[j * width + i] = MAX(0, pixels[j * width + i]-2);
		 }
	 }
	image.update();
}
void ofApp::draw(){
	image.draw(0,0);
}
