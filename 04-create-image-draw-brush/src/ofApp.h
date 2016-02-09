#include "ofMain.h"

class ofApp : public ofBaseApp{
public:
    void setup();
    void update();
    void draw();
    
    unsigned char * pixels;

    int width;
    int height;
    
    ofImage	image;
};