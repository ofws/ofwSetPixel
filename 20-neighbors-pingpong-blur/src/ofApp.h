#include "ofMain.h"
class ofApp : public ofBaseApp{
public:
    void setup();
    void update();
    void draw();

    ofImage	myPicture;
    ofImage	myPictureBlurred;
    
    int	width;
    int	height;
        
    unsigned char * pixelStorage;
	
};

