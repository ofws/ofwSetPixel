#include "ofMain.h"
#include "ofxOpenCv.h"

class ofApp : public ofBaseApp{

public:
    void setup();
    void update();
    void draw();
    
    // create a variable of the type ofImage
    ofImage	myPicture;
    ofxCvGrayscaleImage	myPictureAsCvImage;

};