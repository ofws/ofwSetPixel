#include "ofMain.h"
#include "ofxOpenCv.h"
#include "ofxGui.h"

class ofApp : public ofBaseApp{

public:
    void setup();
    void update();
    void draw();
    
    ofxPanel gui;
    ofxToggle bLearnBg;
    ofxIntSlider threshold;

    int	width, height;
    ofVideoGrabber video;
    ofxCvColorImage videoColorCvImage;
    ofxCvGrayscaleImage	videoGrayscaleCvImage;
    ofxCvGrayscaleImage	videoBgImage;

    ofxCvGrayscaleImage	videoDiffImage;

};
