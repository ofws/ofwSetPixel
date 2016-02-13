#include "ofMain.h"
#include "ofxOpenCv.h"
#include "ofxGui.h"

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
    
};
