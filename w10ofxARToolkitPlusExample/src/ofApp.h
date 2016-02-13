
#include "ofMain.h"
#include "ofxOpenCv.h"
#include "ofxARToolkitPlus.h"

// Uncomment this to use a camera instead of a video file
#define CAMERA_CONNECTED

class ofApp : public ofBaseApp{

public:
    void setup();
    void update();
    void draw();

    void keyPressed  (int key);

    int width, height;

    /* Use either camera or a video file */
    #ifdef CAMERA_CONNECTED
    ofVideoGrabber vidGrabber;
    #else
    ofVideoPlayer vidPlayer;
    #endif

    /* ARToolKitPlus class */	
    ofxARToolkitPlus artk;	
    int threshold;

    ofxCvColorImage colorImage;
    ofxCvGrayscaleImage grayImage;
    ofxCvGrayscaleImage	grayThres;

    /* The four corners of the image */
    vector<ofPoint> displayImageCorners;
	
};

