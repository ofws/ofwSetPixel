

#include "ofMain.h"
#include "ofxVectorGraphics.h"

class ofApp : public ofBaseApp{

public:
    void setup();
    void draw(); 
    void keyPressed  (int key);
    
    ofImage		myPicture;
    ofxVectorGraphics output;
};