
#include "ofMain.h"
#include "ofxOpenCv.h"
#include "ofxGui.h"


class ofApp : public ofBaseApp{

public:
    void setup();
    void update();
    void draw();

    
    ofImage	myPicture;
    ofxCvGrayscaleImage	myPictureAsCvImage;
    ofxPanel gui;
	
    ofxLabel label;
    ofxIntSlider threshold, blurAmount;
    ofxToggle bBlur;
};
