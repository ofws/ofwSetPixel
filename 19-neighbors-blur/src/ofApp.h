#include "ofMain.h"

class ofApp : public ofBaseApp{

public:
    void setup();
    void draw();
    
    ofImage	myPicture;
    ofImage	myPictureBlurred;

    int	width;
    int	height;
};
