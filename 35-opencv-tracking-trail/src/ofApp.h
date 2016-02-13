

#include "ofMain.h"
#include "ofxOpenCv.h"
#include "ofxGui.h"


typedef struct {
	
	ofPoint		pos;
	int			nFramesActive;
	bool		bFoundThisFrame;
	int			whoThisFrame;
	int			id;
	
	ofPoint		posSmooth;
	vector <ofPoint> trail;
	
} tracker;


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
    vector<tracker> trackerObjects;
    int	idCount;
	
	
	
};
