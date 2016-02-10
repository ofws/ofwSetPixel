#include "ofApp.h"

void ofApp::setup(){
    myPicture.load("test.bmp");
    myPicture.setImageType(OF_IMAGE_GRAYSCALE);
		
	width = myPicture.getWidth();
	height = myPicture.getHeight();
	
	pixelStorage = new unsigned char[width*height]; //we will use this later
    ofSetWindowShape(width, height);
}
void ofApp::draw(){
	ofSetColor(255);
	myPicture.draw(0,0);
}

void ofApp::keyPressed(int key){
    
    // get a pointer to the image data:
    unsigned char * pixels = myPicture.getPixels().getData();
    
    // copy the pixels into our pixelStorage
    for (int i = 0; i < width; i++){
        for (int j = 0; j < height; j++){
            int pixIndex = j * width + i;
            pixelStorage[pixIndex]  = pixels[pixIndex];
        }
    }
    
    // now, let's blur from pixels into pixelsBlurred:
    for (int x = 0; x < width; x++){
        for (int y = 0; y < height; y++){
            
            // not accounting for edges.
            /*
             int nw = ((y-1) * width + (x-1));
             int n_ = ((y-1) * width + (x  ));
             int ne = ((y-1) * width + (x+1));
             int _w = ((y  ) * width + (x-1));
             int me = ((y  ) * width + (x  ));
             int _e = ((y  ) * width + (x+1));
             int sw = ((y+1) * width + (x-1));
             int s_ = ((y+1) * width + (x  ));
             int se = ((y+1) * width + (x+1));
             */
            
            int pixIndex = y * width + x;
            
            if(pixels[pixIndex] == 255) //if we're looking at a white pixel
            {
                
                // deal with the edges !! :
                // (using min and max to make sure that we don't go past the 0,0 or the maximum width/height of the image)
                int x_m_1 = MAX(0, x-1);
                int x_p_1 = MIN(width-1, x+1);
                int y_m_1 = MAX(0, y-1);
                int y_p_1 = MIN(height-1, y+1);
                
                //------------------
                
                int nw = (y_m_1 * width + x_m_1);
                int n_ = (y_m_1 * width + x    );
                int ne = (y_m_1 * width + x_p_1);
                int _w = (y     * width + x_m_1);
                int me = (y     * width + x    );
                int _e = (y     * width + x_p_1);
                int sw = (y_p_1 * width + x_m_1);
                int s_ = (y_p_1 * width + x    );
                int se = (y_p_1 * width + x_p_1);
                
                if(pixelStorage[ne] == 0 || pixelStorage[n_] == 0 || pixelStorage[nw] == 0 || pixelStorage[_e] == 0 || pixelStorage[me] == 0 
                   || pixelStorage[_w] == 0 || pixelStorage[se] == 0 || pixelStorage[s_] == 0 || pixelStorage[sw] == 0) // and any of the pixels around it are black
                {
                    pixels[pixIndex]  = 0; // make this pixel back
                }
            }
        }
    }
    myPicture.update();
}
