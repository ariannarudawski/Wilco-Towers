#pragma once

#include "ofMain.h"

class ofApp : public ofBaseApp{

	public:
		void setup();
		void update();
		void draw();

		void keyPressed(int key);
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

private:

	// camera

	ofCamera MainCamera;

	// towers

	ofColor wilcoColor = ofColor(199, 179, 149);

	float towerHeight = 600.0f;

	int numCirclesPerFloor = 16;
	int numFloorsPerTower = 15; 
	int numVertsPerCircle = 40;

	float baseRadius = 157.0f;
	float subCircleRadius = 43.0f;

	ofMesh *** towerStructure;
	ofMesh *** towerWalls;  

	// song information

	ofSoundPlayer song;
	bool playing;
	int fftSampleSize;
	float * fftRaw;
	float * fftSmooth;
};
