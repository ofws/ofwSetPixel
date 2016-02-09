#ifndef _TEST_APP
#define _TEST_APP


#include "ofMain.h"
#include "ofxOpenCv.h"
#include "ofxControlPanel.h"


struct tracker {
	
	ofPoint		pos;
	int			nFramesActive;
	bool		bFoundThisFrame;
	int			whoThisFrame;
	int			id;
	
};


class ofApp : public ofBaseApp{

	public:
		void setup();
		void update();
		void draw();

		void keyPressed  (int key);
		void keyReleased(int key);
		void mouseMoved(int x, int y );
		void mouseDragged(int x, int y, int button);
		void mousePressed(int x, int y, int button);
		void mouseReleased(int x, int y, int button);
		void windowResized(int w, int h);
		
		// create a variable of the type ofImage
		ofxControlPanel			panel;
	
		int						width, height;
		ofVideoGrabber			video;
		ofxCvColorImage			videoColorCvImage;
		ofxCvGrayscaleImage		videoGrayscaleCvImage;
		ofxCvGrayscaleImage		videoBgImage;
		ofxCvGrayscaleImage		videoDiffImage;
	
		ofxCvContourFinder		contourFinder;
		
	
		// this will store all trackers...
		vector < tracker >		trackerObjects;
		int						idCount;
	
	
	
};

#endif