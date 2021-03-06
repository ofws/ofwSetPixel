#include "ofApp.h"
void ofApp::setup(){
	myPicture.load("test.bmp");
	myPicture.setImageType(OF_IMAGE_GRAYSCALE);
		
	width= myPicture.getWidth();
	height = myPicture.getHeight();
		
	pixelStorage = new unsigned char[width*height]; //we will use this later
    scale = 5;
    ofSetWindowShape(width*scale, height*scale);
}

void ofApp::draw(){
	
	ofSetColor(255);
	myPicture.draw(0,0, width*scale, height*scale);
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
    
    
    for (int x = 0; x < width; x++){
        for (int y = 0; y < height; y++){
            
            int pixIndex = y * width + x;
            
            //if(pixels[pixIndex] == 0) //if this pixel is alive
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
                int me = (y		* width + x		);
                int ne = (y_m_1 * width + x_p_1);
                int _w = (y     * width + x_m_1);
                int _e = (y     * width + x_p_1);
                int sw = (y_p_1 * width + x_m_1);
                int s_ = (y_p_1 * width + x    );
                int se = (y_p_1 * width + x_p_1);
                
                int numNeighbors = 0;
                
                if(pixelStorage[nw]==0 && nw != n_ && nw != me)
                    numNeighbors++;
                
                if(pixelStorage[n_]==0 && n_ != me)
                    numNeighbors++;
                
                if(pixelStorage[ne]==0 && ne != n_ && ne != me)
                    numNeighbors++;
                
                if(pixelStorage[_w]==0 && _w != me)
                    numNeighbors++;
                
                if(pixelStorage[_e]==0 && _e != me)
                    numNeighbors++;
                
                if(pixelStorage[sw]==0 && sw != s_ && sw != me)
                    numNeighbors++;
                
                if(pixelStorage[s_]==0 & s_ != me)
                    numNeighbors++;
                
                if(pixelStorage[se]==0 && se != s_ && se != me)
                    numNeighbors++;
                
                
                if(pixelStorage[me]==0)
                    cout<<x<<", "<<y<<" : "<<numNeighbors<<endl;
                
                //Any live cell with fewer than two live neighbours dies, as if caused by under-population.
                //Any live cell with two or three live neighbours lives on to the next generation.
                //Any live cell with more than three live neighbours dies, as if by overcrowding.
                //Any dead cell with exactly three live neighbours becomes a live cell, as if by reproduction.
                
                if(numNeighbors < 2)
                    pixels[pixIndex]  = 255; // kill me
                else if(numNeighbors <= 3)
                {
                    pixels[pixIndex] = pixels[pixIndex]; //if live stay alive
                    
                    if(numNeighbors == 3)
                        pixels[pixIndex] = 0; //make me alive if i was not alive
                }
                else if(numNeighbors > 3)
                    pixels[pixIndex]  = 255; // kill me
            }
        }
    }
    myPicture.update();
}
