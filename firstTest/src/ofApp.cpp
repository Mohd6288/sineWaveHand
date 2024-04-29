#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup() {
	// Initialize webcam
	vidGrabber.setVerbose(true);
	vidGrabber.setDeviceID(0);
	vidGrabber.setup(ofGetWidth(), ofGetHeight());

	// Allocate images based on webcam size
	grayImage.allocate(vidGrabber.getWidth(), vidGrabber.getHeight());
	grayBg.allocate(vidGrabber.getWidth(), vidGrabber.getHeight());
	grayDiff.allocate(vidGrabber.getWidth(), vidGrabber.getHeight());
	colorImg.allocate(vidGrabber.getWidth(), vidGrabber.getHeight());

	minArea = 10 * 10; // Example: minimum area of 100 pixels
	maxArea = 320 * 240; // Example: maximum area of half the video feed
	// Setup audio
	ofSoundStreamSetup(2, 0, this, 44100, 512, 4); // 2 output channels, 44100 Hz sample rate, 512 buffer size
	frequency = 440; // Starting frequency, e.g., A4
	amplitude = 1;
}

//--------------------------------------------------------------
void ofApp::update() {
	vidGrabber.update();
	
	if (vidGrabber.isFrameNew()) {
		colorImg.setFromPixels(vidGrabber.getPixels());
		grayImage = colorImg;

		// Find difference between background and current frame
		grayDiff.absDiff(grayBg, grayImage);
		grayDiff.threshold(150);
		// Find contours
		//contourFinder.findContours(grayDiff, 20, (340 * 240) / 2, 150, true);
		contourFinder.findContours(grayDiff, 20, 340*240, 150, true);

		// Clear the previous frame's blob data
		blobsData.clear();

		// Store current frame's blob data
		for (int i = 0; i < contourFinder.nBlobs; i++) {
			ofxCvBlob& blob = contourFinder.blobs[i];
			blobsData.emplace_back(blob.centroid.x, blob.centroid.y, blob.boundingRect.width, blob.boundingRect.height);
		}
	}

	if (!blobsData.empty()) {
		// Example: Modifying frequency and amplitude based on the first blob
		frequency = ofMap(blobsData[0].position.x, 0, ofGetWidth(), 200, 1000); // Map x position to frequency
		amplitude = 0.5;
	}
}

//--------------------------------------------------------------
void ofApp::draw() {


	// Draw grayscale difference and images
	ofSetHexColor(0xffffff);
	const int secWidth = ofGetWidth() / 4;
	const int secHeight = 240;

	grayDiff.draw(0, 0, secWidth, secHeight);
	colorImg.draw(secWidth, 0, secWidth, secHeight);
	grayBg.draw(2 * secWidth, 0, secWidth, secHeight);
	grayImage.draw(3 * secWidth, 0, secWidth, secHeight);

	// Draw contourFinder
	ofFill();
	ofSetHexColor(0x333333);
	// Draw all contours with a standard color
	ofSetColor(255, 255, 255); // White color for all contours
	
	for (int i = 0; i < contourFinder.nBlobs; i++) {
		contourFinder.blobs[i].draw(0, 0);
		// Get the centroid of the blob
		ofPoint center = contourFinder.blobs[i].centroid;

		// Get the size of the blob
		float width = contourFinder.blobs[i].boundingRect.width;
		float height = contourFinder.blobs[i].boundingRect.height;

		// Create a string with position and size information
		stringstream blobInfo;
		blobInfo << "Blob " << i << ": X=" << center.x << ", Y=" << center.y
			<< ", Width=" << width << ", Height=" << height;

		// Draw the string on the screen
		ofDrawBitmapString(blobInfo.str(), center.x + 20, center.y);
	}

	// Highlight detected hands
	ofSetColor(0, 255, 0); // Green color for detected hands
	
}


//--------------------------------------------------------------
void ofApp::keyPressed(int key){
	/*
	cout << "This is nblobs number" << contourFinder.nBlobs << endl;
	cout << "This is blobs data" << contourFinder.blobs.data() << endl;
	cout << "This is blobs size" << contourFinder.blobs.size() << endl;
	cout << "This is blobs capacity" << contourFinder.blobs.capacity() << endl;
	*/
	someMethodToHandleSound();

}

//--------------------------------------------------------------
void ofApp::someMethodToHandleSound() {
	for (BlobData& blob : blobsData) {
		// Example: Map blob's x position to pan, and width to pitch
		float pan = ofMap(blob.position.x, 0, ofGetWidth(), -1, 1);
		float pitch = ofMap(blob.width, 0, ofGetWidth(), 0.5, 2.0);

		// Now use 'pan' and 'pitch' to control your sound
		// This would depend on your sound library or setup
		cout << pan << pitch <<endl;
	}
}
//--------------------------------------------------------------
void ofApp::keyReleased(int key){

}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){

}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseEntered(int x, int y){

}

//--------------------------------------------------------------
void ofApp::mouseExited(int x, int y){

}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){

}

void ofApp::audioOut(ofSoundBuffer& buffer) {
	for (size_t i = 0; i < buffer.getNumFrames(); ++i) {
		wave = amplitude * mySine.sinewave(frequency); // Apply amplitude and frequency
		buffer[i * buffer.getNumChannels()] = wave; // Left channel
		buffer[i * buffer.getNumChannels() + 1] = wave; // Right channel
	}
}


//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){ 

}
