#include "ofMain.h"
class ofApp : public ofBaseApp{
public:
    void setup();
    void update();
    void draw();
    
    unsigned char * pixels;
    // we do this as a pointer.  don't worry!  it's just easier to allocate
    // the memory in setup then on the stack.  will explain!

    int width;
    int height;
    
    ofImage image;
};