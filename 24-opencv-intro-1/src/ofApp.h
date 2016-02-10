
#include "ofMain.h"
#include "ofxOpenCv.h"

class ofApp : public ofBaseApp{

public:
    void setup();
    void draw();
    
    ofImage					myPicture;
    ofxCvGrayscaleImage		myPictureAsCvImage;
	
};
