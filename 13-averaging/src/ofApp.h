#include "ofMain.h"

class ofApp : public ofBaseApp{

public:
    void setup();
    void draw();

    ofImage	myPictures[4];
    int	*pixelsSum;
    int	width;
    int	height;

    ofImage	averageImg;
};