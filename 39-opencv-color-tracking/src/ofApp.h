
#include "ofMain.h"
#include "ofxOpenCv.h"
#include "ofxGui.h"

// color tracking

class ofApp : public ofBaseApp{

public:
    void setup();
    void update();
    void draw();
    void keyPressed(int key);
    void mousePressed(int x, int y, int button);
    
    ofxPanel gui;
    ofxToggle bShowDebug;

    ofxIntSlider hueRange, satRange, briRange;

    // for tracking...
    int hue, sat, bri;

    int	width, height;
    ofVideoGrabber video;
    ofxCvColorImage videoColorCvImage;
    ofxCvColorImage videoColorHSVCvImage;

    ofxCvGrayscaleImage videoGrayscaleHueImage;
    ofxCvGrayscaleImage videoGrayscaleSatImage;
    ofxCvGrayscaleImage videoGrayscaleBriImage;
    
    unsigned char * grayPixels;
    ofxCvGrayscaleImage videoGrayscaleCvImage;
};
