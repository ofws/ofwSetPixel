#pragma once
#include "ofMain.h"
class ofApp : public ofBaseApp{
public:
    void setup();
    void draw();

    void keyPressed  (int key);
    
    ofImage	myPicture;
    unsigned char * pixelStorage;

    int	width;
    int	height;
    int scale;
};
