#include "ofApp.h"

int compare( const void *a,  const void *b){
	unsigned char *aPtr = ( unsigned char *)a;
    unsigned char *bPtr = ( unsigned char *)b;
	unsigned char valuea = *aPtr;
	unsigned char valueb = *bPtr;
	if (valuea > valueb) return 1;
	else return -1;
}

void ofApp::setup(){
    myPicture.load("test.png");
	myPicture.setImageType(OF_IMAGE_GRAYSCALE);
	
	width = myPicture.getWidth();
	height = myPicture.getHeight();
	
	myPictureSorted.allocate(width, height, OF_IMAGE_GRAYSCALE);
	unsigned char * sortedPixels = myPictureSorted.getPixels().getData();
	unsigned char * pixelsFromImage = myPicture.getPixels().getData();
    
    //copy every pixel
	for (int x = 0; x < width; x++){
		for (int y = 0; y < height; y++){
			int pixIndex = y * width + x;
			sortedPixels[pixIndex] = pixelsFromImage[pixIndex];
		}
	}

    //sort
    //qsort(<#void *#>, <#size_t#>, <#size_t#>, <#int (*)(const void *, const void *)#>)
	qsort(sortedPixels, width*height, sizeof(unsigned char), compare);
	myPictureSorted.update();
    
    ofSetWindowShape(width*2, height);
}

void ofApp::draw(){
	ofSetColor(255);
	myPicture.draw(0,0);
	myPictureSorted.draw(width, 0);
}