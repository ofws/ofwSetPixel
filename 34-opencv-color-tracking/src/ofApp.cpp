#include "ofApp.h"
void ofApp::setup(){
	video.initGrabber(320, 240);
    width = video.getWidth();
	height = video.getHeight();
	
	videoColorCvImage.allocate(width, height);
	videoColorHSVCvImage.allocate(width, height);
	
	videoGrayscaleHueImage.allocate(width, height);
	videoGrayscaleSatImage.allocate(width, height);
	videoGrayscaleBriImage.allocate(width, height);
	
	videoGrayscaleCvImage.allocate(width, height);
	
	grayPixels = new unsigned char [width * height];
	
    gui.setup("", "settings.xml", 10, height*2 +10);
    gui.add(bShowDebug.setup("show debug (h)", true));
    gui.add(hueRange.setup("hue range", 20, 0, 255));
    gui.add(satRange.setup("sat range", 30, 0, 255));
    gui.add(briRange.setup("bri range", 25, 0, 255));
	
	hue = 0;
	sat = 0;
	bri = 0;
    
    ofSetWindowShape(width*3, height*2 + 120);
}

void ofApp::update(){
    video.update();
	if (video.isFrameNew()){
        
		videoColorCvImage.setFromPixels(video.getPixels().getData(), width, height);
		videoColorHSVCvImage = videoColorCvImage;
		videoColorHSVCvImage.convertRgbToHsv();
		
		videoColorHSVCvImage.convertToGrayscalePlanarImages(videoGrayscaleHueImage, videoGrayscaleSatImage, videoGrayscaleBriImage);
		
		unsigned char * colorHsvPixels = videoColorHSVCvImage.getPixels().getData();
		
		for (int i = 0; i < width*height*3; i+=3){ //threshold!
			
				// since hue is cyclical:
				int hueDiff = colorHsvPixels[i] - hue;
				if (hueDiff < -127) hueDiff += 255;
				if (hueDiff > 127) hueDiff -= 255;
			
			
				if ( (fabs(hueDiff) < hueRange) &&
					(colorHsvPixels[i+1] > (sat - satRange) && colorHsvPixels[i+1] < (sat + satRange)) &&
					(colorHsvPixels[i+2] > (bri - briRange) && colorHsvPixels[i+2] < (bri + briRange))){
	
					grayPixels[i/3] = 255;
		
				} else {
					grayPixels[i/3] = 0;
				}
			}
			videoGrayscaleCvImage.setFromPixels(grayPixels, width, height);
		
		//optional
		//videoGrayscaleCvImage.dilate();
		//videoGrayscaleCvImage.erode();
	}
	
}

void ofApp::draw(){
    ofBackgroundGradient(80,0);
	
	ofSetColor(255);
    videoColorCvImage.draw(0,0);
    videoGrayscaleCvImage.draw(width,0);
    videoColorHSVCvImage.draw(width*2, 0);
	videoGrayscaleHueImage.draw(0,height);
    videoGrayscaleSatImage.draw(width,height);
    videoGrayscaleBriImage.draw(width*2,height);
    
    if (bShowDebug){
        ofDrawBitmapStringHighlight("click to pick color", 0, height);
        ofDrawBitmapStringHighlight("tracked color", width, height);
        ofDrawBitmapStringHighlight("HSV as RGB", width*2, height);
        ofDrawBitmapStringHighlight("hue as grey", 0, height*2);
        ofDrawBitmapStringHighlight("sat as grey", width, height*2);
        ofDrawBitmapStringHighlight("bri as grey", width*2, height*2);
        
        gui.draw();
    }
    
}


void ofApp::keyPressed(int key){
    if (key == 'h'){
        bShowDebug = !bShowDebug;
    }
}

void ofApp::mousePressed(int x, int y, int button){
	 // we *could* be just using the different components of videoColorCvImage here, but we're using the gray images instead as illustration
	if (x >= 0 && x < width && y >= 0 && y < height){
		int pixel = y * width + x;
		hue = videoGrayscaleHueImage.getPixels()[pixel];
		sat = videoGrayscaleSatImage.getPixels()[pixel];
		bri = videoGrayscaleBriImage.getPixels()[pixel];
		
	}
}