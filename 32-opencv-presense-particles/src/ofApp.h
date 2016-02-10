
#include "ofMain.h"
#include "ofxOpenCv.h"
#include "ofxGui.h"

#include "particle.h"

class ofApp : public ofBaseApp{

public:
    void setup();
    void update();
    void draw();

    void keyPressed  (int key);
    
    ofxPanel gui;
    ofxToggle bLearnBg, bDrawDebug, bDrawGui;
    ofxIntSlider threshold;

    int	width, height;
    ofVideoGrabber video;
    ofxCvColorImage	videoColorCvImage;
    ofxCvGrayscaleImage	videoGrayscaleCvImage;
    ofxCvGrayscaleImage	 videoBgImage;
    ofxCvGrayscaleImage	videoDiffImage;
    
    vector < particle > particles;
    unsigned pResetCounter;
};
