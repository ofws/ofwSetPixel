#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
	
	myPicture.load("brucelee1.tif");
	myPicture.setImageType(OF_IMAGE_GRAYSCALE);
		
	width = myPicture.getWidth();
	height = myPicture.getHeight();
	
	myPictureSquares.allocate(width, height, OF_IMAGE_GRAYSCALE);
	
	unsigned char * pixels = myPicture.getPixels().getData();
	unsigned char * pixelsSquare = myPictureSquares.getPixels().getData();
	
    for(int i = 0; i < width*height; i++){
		pixelsSquare[i] = 255;
    }
    
	// now check each pixel from the image for a square
	bool foundSquare = true;
	int largestFoundSquareSize = 1;
	int largestFoundSquareStartX;
	int largestFoundSquareStartY;
	
	while(foundSquare){
		foundSquare = false;
		for (int y = 0; y < height; y++){
			for (int x = 0; x < width; x++){
                // get the index of where we are
				int pixIndex = y * width + x;
                
				// if we are a black pixel, figure out the width and height of the rectangle that we are
				if(pixels[pixIndex] == 0){
					foundSquare = true;
					
					int squareLength = 1;
					int squareHeight = 1;
                    
					// go from our pixel to the end (or until we hit a white pixel) for the initial row
					for(int l=x;l<width;l++){
                        //figure out where we are
						int lengthPixIndex = y * width + l;
						//if the pixel we are looking at is black
						if(pixels[lengthPixIndex] < 255){
							//increase our length
                            squareLength++;
						}
                        //otherwise, stop looking at pixels
                        //break will break us out of any loop we are in,
                        else break;
					}
					
					//now look vertially, and for each black pixel down, check each row entirely to make sure its the same size across
                    // go from our pixel to the end (or until we hit a white pixel)

					for(int h=y;h<height;h++){
                        //figure out where we are
						int heightPixIndex = h * width + x;
                        //if the pixel we are looking at is black
						if(pixels[heightPixIndex] < 255){
                            //increase our height
							squareHeight++;
							// check each row
							int tempLength = 1;
							// go from our pixel to the maximum length we've found so far (or until we hit a white pixel) for each y value
							for(int l = x; l < x+squareLength; l++){
                                //figure out where we are
								int lengthPixIndex = h * width + l;
                                //if the pixel we are looking at is black
								if(pixels[lengthPixIndex] < 255) {
									//increase our length
                                    tempLength++;
								}
                                //otherwise, stop looking at pixels
								else break;
							}
							//if we're smaller, shrink the square
							if(tempLength < squareLength) squareLength = tempLength;
						}
                        //otherwise, stop looking at pixels
						else break;
					}
					
					//now that we have length and width, set them both to the smaller one (since we're looking for squares only)
					int squareSize = MIN(squareLength, squareHeight);
					
					// if the size of our square is the largest square in the image so far, update that information
					if(squareSize >= largestFoundSquareSize){
						largestFoundSquareStartX = x;
						largestFoundSquareStartY = y;
						largestFoundSquareSize = squareSize;
					}
		
				}
			}
		}
		//if we've found a square, move the one we've found (since it's the largest), and then go through the image again)
		if(foundSquare){
			//now that we know how big our square is, go through again and remove it from the origional image, and then add it to the myPictureSquares
            //from our start x, to the length of the square
			for(int _x = largestFoundSquareStartX; _x < largestFoundSquareStartX+largestFoundSquareSize; _x++){
                //from our start, y to the height of the square
				for(int _y = largestFoundSquareStartY; _y < largestFoundSquareStartY+largestFoundSquareSize; _y++){
                    //figure out where we are
					int squarePixIndex = _y * width + _x;
					// set the pixel in the origional image to white
					pixels[squarePixIndex] = 255;
                    
                    // if we're on one of the square's edges
					if(_x == largestFoundSquareStartX || _y == largestFoundSquareStartY || _x == largestFoundSquareStartX+largestFoundSquareSize-1 || _y == largestFoundSquareStartY+largestFoundSquareSize-1)
                        
                        // set the pixel in our pixel storage to white
                        pixelsSquare[squarePixIndex] = 255;
					
                    else
                        // otherwise set the pixel in our pixel storage to black, this is how we get borders
						pixelsSquare[squarePixIndex] = 0;
				}
			}
            //reset found square size
			largestFoundSquareSize = 1;
		}
	}
	
	myPictureSquares.update();
    ofSetWindowShape(width*2, height);
}
void ofApp::draw(){
	ofSetColor(255);
	myPicture.draw(0,0);
	myPictureSquares.draw(width,0);
}
