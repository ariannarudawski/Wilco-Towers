#include "ofMain.h"
#include "ofApp.h"

//========================================================================
int main() {

	// 1 x 1
	//ofSetupOpenGL(1024, 1024, OF_WINDOW);			// <-------- setup the GL context

	// 9 x 16
	// ofSetupOpenGL(864, 1536, OF_WINDOW);			// <-------- setup the GL context
	ofSetupOpenGL(720 * 1.3, 1280 * 1.3, OF_WINDOW);			// <-------- setup the GL context

	// this kicks off the running of my app
	// can be OF_WINDOW or OF_FULLSCREEN
	// pass in width and height too:
	ofRunApp(new ofApp());

}
