#include "ofMain.h"

class ofApp : public ofBaseApp{

public:
    void setup();
    void update();
    void draw();
    void keyPressed  (int key);

    ofTrueTypeFont helvetica;

    bool * pixels;
    int width;
    int height;

    int position;

};