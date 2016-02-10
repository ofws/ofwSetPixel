#include "ofMain.h"
#include "ofxOpenCv.h"
#include "ofxGui.h"

class ofApp : public ofBaseApp{
public:
    void setup();
    void update();
    void draw();

    int	width, height;
    
    ofxPanel gui;
    ofxIntSlider threshold;
    
    ofVideoGrabber video;
    ofxCvColorImage	videoColorCvImage;
    ofxCvGrayscaleImage	videoGrayscaleCvImage;
    ofxCvGrayscaleImage	videoPrevFrameImage;

    ofxCvGrayscaleImage	videoDiffImage;
};
