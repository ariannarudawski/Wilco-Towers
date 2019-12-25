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

	float towerHeight = 800.0f;

	int numDiscsPerTower = 100; 
	int numVertsPerDisc = 100;

	float baseRadius = 200.0f;

	ofMesh * tower0;
	ofMesh * tower1;

	// build "animation"

	bool tower0building;
	bool tower1building; 

	int buildCounter0 = 0;
	int buildCounter1 = 0;		
};
