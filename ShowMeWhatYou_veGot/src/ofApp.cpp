#include "ofApp.h"

bool showStuff = true;
float dispWidth = 640;
float dispHeight = 480;

//--------------------------------------------------------------
void ofApp::setup() {
	camWidth = 960;
	camHeight = 720;

	vidGrabber.setDeviceID(0);
	vidGrabber.initGrabber(camWidth, camHeight);

	finder.setup("haarcascade_frontalface_default.xml");

	rgb.allocate(camWidth, camHeight);
	hsb.allocate(camWidth, camHeight);
	hue.allocate(camWidth, camHeight);
	sat.allocate(camWidth, camHeight);
	bri.allocate(camWidth, camHeight);
	filter1.allocate(camWidth, camHeight);
	filter2.allocate(camWidth, camHeight);
	finalImage.allocate(camWidth, camHeight);
	
}

//--------------------------------------------------------------
void ofApp::update() {
	vidGrabber.update();

	if (vidGrabber.isFrameNew())
	{
		rgb.setFromPixels(vidGrabber.getPixels());
		hsb = rgb;
		hsb.convertRgbToHsv();
		hsb.convertToGrayscalePlanarImages(hue, sat, bri);

		int hueRange = 10;
		for (int i = 0; i < camWidth * camHeight; ++i) {
			filter1.getPixels()[i] = ofInRange(hue.getPixels()[i],
				findHue - hueRange,
				findHue + hueRange) ? 255 : 0;
		}
		filter1.flagImageChanged();

		int satRange = 20;
		for (int i = 0; i < camWidth * camHeight; ++i) {
			filter2.getPixels()[i] = ofInRange(sat.getPixels()[i],
				findSat - satRange,
				findSat + satRange) ? 255 : 0;
		}
		filter2.flagImageChanged();

		cvAnd(filter1.getCvImage(),
			filter2.getCvImage(),
			finalImage.getCvImage());
		finalImage.flagImageChanged();

		finder.findHaarObjects(vidGrabber.getPixels());
	}
}

//--------------------------------------------------------------
void ofApp::draw() {
	if (showStuff) {
		ofSetColor(ofColor::white);
		ofBackground(ofColor::black);

		sat.draw(0,0, ofGetWindowWidth(), ofGetWindowHeight());
		
	}
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key) {
	if (key == ' ')
		showStuff = !showStuff;
}

//--------------------------------------------------------------
void ofApp::keyReleased(int key) {

}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y) {

}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button) {

}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button) {


}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button) {

}

//--------------------------------------------------------------
void ofApp::mouseEntered(int x, int y) {

}

//--------------------------------------------------------------
void ofApp::mouseExited(int x, int y) {

}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h) {
//	dispHeight = h;
//	dispWidth = w;
//	if (h / w < 0.75) {
//		// this means the width is bigger
//		dispWidth = h * 0.75;
//	}
//	if (h / w > 0.75) {
//		// this means the height is bigger
//		dispHeight = w * (4.0 / 3.0);
//	}
}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg) {

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo) {

}