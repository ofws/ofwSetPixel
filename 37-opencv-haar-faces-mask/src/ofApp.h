

#include "ofMain.h"
#include "ofxOpenCv.h"
#include "ofxGui.h"

typedef struct {
	
	ofPoint		pos;
	ofPoint		posSmooth;
	float		width;
	float		widthSmooth;

	float		energy;
	int			nFramesAlive;
	bool		bFoundThisFrame;
	int			whoThisFrame;
	int			id;
	
} tracker;


class ofApp : public ofSimpleApp{

public:

    void setup();
    void update();
    void draw();
  
    ofxPanel gui;
    ofxFloatSlider scaleHaar;
    
    int width, height;
    ofVideoGrabber video;
    ofxCvColorImage	colorImg;
    ofxCvGrayscaleImage grayImage;
    ofxCvHaarFinder	haarFinder;

    // this will store all trackers...
    vector<tracker> trackerObjects;
    int	idCount;
    
    ofImage	maskImage[3];
};
