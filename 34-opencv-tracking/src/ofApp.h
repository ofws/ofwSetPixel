
#include "ofMain.h"
#include "ofxOpenCv.h"
#include "ofxGui.h"


struct tracker {
	
	ofPoint	pos;
	int	nFramesActive;
	bool bFoundThisFrame;
	int	whoThisFrame;
	int	id;
	
};


class ofApp : public ofBaseApp{

public:
    void setup();
    void update();
    void draw();
		
    ofxPanel gui;
    ofxToggle bLearnBg;
    ofxIntSlider threshold, nDilations, nErosions;
    ofxIntSlider minBlobSize, maxBlobSize, nBlobsTofind;
	
    int	width, height;
    ofVideoGrabber video;
    ofxCvColorImage	videoColorCvImage;
    ofxCvGrayscaleImage	videoGrayscaleCvImage;
    ofxCvGrayscaleImage	videoBgImage;
    ofxCvGrayscaleImage	videoDiffImage;

    ofxCvContourFinder contourFinder;
    
    // this will store all trackers...
    vector<tracker>	trackerObjects;
    int	idCount;
	
};