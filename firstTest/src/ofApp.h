#pragma once

#include "ofMain.h"
#include "ofxOpenCv.h"
#include "ofxMaxim.h";

// Define BlobData class
class BlobData {
public:
	ofPoint position; // Stores the x, y coordinates
	float width, height; // Stores the width and height

	BlobData(float x, float y, float w, float h) : position(x, y), width(w), height(h) {}
};

class ofApp : public ofBaseApp{

	public:
		void setup();
		void update();
		void draw();

		void keyPressed(int key);
		void someMethodToHandleSound();
		void keyReleased(int key);
		void mouseMoved(int x, int y );
		void mouseDragged(int x, int y, int button);
		void mousePressed(int x, int y, int button);
		void mouseReleased(int x, int y, int button);
		void mouseEntered(int x, int y);
		void mouseExited(int x, int y);
		void windowResized(int w, int h);
		void dragEvent(ofDragInfo dragInfo);
		void gotMessage(ofMessage msg);

		//video grabber webcam
		ofVideoGrabber vidGrabber;
		ofxCvColorImage colorImg;
		ofxCvGrayscaleImage grayImage, grayBg, grayDiff; // grayscale depth image// the background image// the background image// an image for storing the foreground image based on the bg image
		ofxCvContourFinder contourFinder;
		//class vector
		vector<BlobData> blobsData; // Vector to store blob data

		// Audio components
		maxiOsc mySine; // Sine wave oscillator (using ofxMaxim)
		double frequency; // Frequency of the sine wave
		double wave; // Output of the sine wave
		float amplitude;
		float minArea;
		float maxArea;
		// Method to update sound
		void audioOut(ofSoundBuffer& buffer);
		bool one = false;
};
