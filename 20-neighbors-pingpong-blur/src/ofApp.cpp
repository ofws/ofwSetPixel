#include "ofApp.h"

void ofApp::setup(){
	myPicture.load("test.png");
	myPicture.setImageType(OF_IMAGE_GRAYSCALE);
	
	// allocate pixels and texture for this image. 
	width = myPicture.getWidth();
	height = myPicture.getHeight();
	
	myPictureBlurred.allocate(width, height, OF_IMAGE_GRAYSCALE);
	
    //we will use this later when we 'ping pong' the blur.
	pixelStorage = new unsigned char[width*height];
    
	// get a pointer to the image data:
	unsigned char * pixels = myPicture.getPixels().getData();
	unsigned char * pixelsBlurred	= myPictureBlurred.getPixels().getData();
	
	// now, let's blur from pixels into pixelsBlurred:
	for (int x = 0; x < width; x++){
		for (int y = 0; y < height; y++){
			
			// not accounting for edges. 
			/*
			 int nw = ((y-1) * width + (x-1));
			 int n_ = ((y-1) * width + (x  ));
			 int ne = ((y-1) * width + (x+1));
			 int _w = ((y  ) * width + (x-1));
			 int me = ((y  ) * width + (x  ));
			 int _e = ((y  ) * width + (x+1));
			 int sw = ((y+1) * width + (x-1));
			 int s_ = ((y+1) * width + (x  ));
			 int se = ((y+1) * width + (x+1));
			 */
			
			int pixIndex = y * width + x;
			
			// deal with the edges !! :	
			// (using min and max to make sure that we don't go past the 0,0 or the maximum width/height of the image)
			int x_m_1 = MAX(0, x-1);
			int x_p_1 = MIN(width-1, x+1);
			int y_m_1 = MAX(0, y-1);
			int y_p_1 = MIN(height-1, y+1);
			
			//------------------
			
			int nw = (y_m_1 * width + x_m_1);
			int n_ = (y_m_1 * width + x    );
			int ne = (y_m_1 * width + x_p_1);
			int _w = (y     * width + x_m_1);
			int me = (y     * width + x    );
			int _e = (y     * width + x_p_1);
			int sw = (y_p_1 * width + x_m_1);
			int s_ = (y_p_1 * width + x    );
			int se = (y_p_1 * width + x_p_1);
			
			int newValue =	pixels[ne] + pixels[n_] + pixels[nw] + pixels[_e] + pixels[me] + pixels[_w] + 
			pixels[se] + pixels[s_] + pixels[sw];
			
			newValue /= 9; //each value is the average of all the pixels around it
			
			pixelsBlurred[pixIndex]  = newValue;
		}
	}
	myPictureBlurred.update();
    
    ofSetWindowShape(width*2, height);
}
void ofApp::update(){
	
	unsigned char * pixelsFromImage = myPicture.getPixels().getData();
	unsigned char * pixelsBlurred = myPictureBlurred.getPixels().getData();
	
	// we are going to blur the pictures into pixelsBlurred, but then copy the pixels back to pixelStorage and do the blur again,
	// because we don't want to contaminate our original pixels, we are using another array of pixels called pixel storage
	
	// copy the pixels into our pixelStorage from the uncontaminated picture
	for (int i = 0; i < width; i++){
		for (int j = 0; j < height; j++){
			int pixIndex = j * width + i;
			pixelStorage[pixIndex]  = pixelsFromImage[pixIndex];
		}
	}
    
	for (int i = 0; i < (mouseX / 5); i++){
		// now, let's blur from pixels into pixelsBlurred:
		for (int x = 0; x < width; x++){
			for (int y = 0; y < height; y++){
				
				int pixIndex = y * width + x;
				
				int x_m_1 = MAX(0, x-1);
				int x_p_1 = MIN(width-1, x+1);
				int y_m_1 = MAX(0, y-1);
				int y_p_1 = MIN(height-1, y+1);
				
				int nw = (y_m_1 * width + x_m_1);
				int n_ = (y_m_1 * width + x    );
				int ne = (y_m_1 * width + x_p_1);
				int _w = (y     * width + x_m_1);
				int me = (y     * width + x    );
				int _e = (y     * width + x_p_1);
				int sw = (y_p_1 * width + x_m_1);
				int s_ = (y_p_1 * width + x    );
				int se = (y_p_1 * width + x_p_1);
				
				int newValue =	pixelStorage[ne] + pixelStorage[n_] + pixelStorage[nw] + pixelStorage[_e] + pixelStorage[me] + pixelStorage[_w] + 
				pixelStorage[se] + pixelStorage[s_] + pixelStorage[sw];
				
				newValue /= 9; //each value is the average of all the pixels around it
				
				pixelsBlurred[pixIndex]  = newValue;
			}
		}
		// fast copy of memory -- copy blurred back to pixelStorage:
		// memcpy ->  (dst, src, number of bytes)
		memcpy(pixelStorage, pixelsBlurred, width*height);
	}
	myPictureBlurred.update();
}

void ofApp::draw(){
	ofSetColor(255);
	myPicture.draw(0,0);
	myPictureBlurred.draw(width, 0);
}
