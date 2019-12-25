#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup()
{
	ofSetVerticalSync(true);
	ofSetFrameRate(30.0);
	ofBackground(wilcoColor);
	ofSetBackgroundAuto(true);
	ofSetWindowShape(1000, 1000);

	// set up camera

	MainCamera.setGlobalPosition(glm::vec3(0.0f, 800, -600.0f));
	MainCamera.lookAt(glm::vec3(0, 0, 0));

	// set up two towers

	towerStructure = new ofMesh**[2];
	towerWalls = new ofMesh**[2];

	float zStep = towerHeight / numFloorsPerTower;
	ofPoint start = ofVec3f(0, 0, 0);
	//ofVec3f startPositions[2] = { ofVec3f(173, -700, -100), ofVec3f(-255, 100, 0) };
	ofVec3f startPositions[2] = { ofVec3f(193, -700, -100), ofVec3f(-205, -50, 0) };

	for (int t = 0; t < 2; t++)
	{
		towerStructure[t] = new ofMesh *[numFloorsPerTower];
		towerWalls[t] = new ofMesh *[numFloorsPerTower - 1];

		for (int f = 0; f < numFloorsPerTower; f++)
		{
			start.set(startPositions[t] + ofVec3f(0, 0, -zStep * f));

			towerStructure[t][f] = new ofMesh[numCirclesPerFloor];

			for (int c = 0; c < numCirclesPerFloor; ++c)
			{
				towerStructure[t][f][c].setMode(OF_PRIMITIVE_TRIANGLE_FAN);

				// create floors/ceilings (won't render, but will use to make walls

				float circleX, circleY, circleZ;
				float subCircleX, subCircleY, subCircleZ;

				float vertAngle = c * TWO_PI / numCirclesPerFloor;

				circleX = start.x + baseRadius * cos(vertAngle);
				circleY = start.y + baseRadius * sin(vertAngle);
				circleZ = start.z;

				ofPoint subCircleStart = ofVec3f(circleX, circleY, circleZ);

				for (int v = 0; v < numVertsPerCircle; ++v)
				{
					float vertAngleSubCircle = v * TWO_PI / numVertsPerCircle;

					subCircleX = subCircleStart.x + subCircleRadius * cos(vertAngleSubCircle);
					subCircleY = subCircleStart.y + subCircleRadius * sin(vertAngleSubCircle);
					subCircleZ = subCircleStart.z;

					ofPoint point = ofVec3f(subCircleX, subCircleY, subCircleZ);
					towerStructure[t][f][c].addVertex(point);
				}
			}
		}

		// make walls

		for (int f = 0; f < numFloorsPerTower - 1; f++)
		{
			towerWalls[t][f] = new ofMesh[numCirclesPerFloor];

			for (int c = 0; c < numCirclesPerFloor; c++)
			{
				// add vertices to towerwalls[f], pull from towerstructure[f] and towerstructure[f+1]
				towerWalls[t][f][c].setMode(OF_PRIMITIVE_TRIANGLE_STRIP);

				for (int v = 0; v < numVertsPerCircle; v++)
				{
					towerWalls[t][f][c].addVertex(towerStructure[t][f][c].getVertex(v));
					towerWalls[t][f][c].addVertex(towerStructure[t][f + 1][c].getVertex(v));
				}

				// add the first two verts again to complete the circle

				towerWalls[t][f][c].addVertex(towerStructure[t][f][c].getVertex(0));
				towerWalls[t][f][c].addVertex(towerStructure[t][f + 1][c].getVertex(0));
			}
		}
	}

	// set up sound

	song.load("heavymetaldrummer.wav");
	song.setLoop(false);
	song.setVolume(0.8f);
	playing = false;

	// we're going to get more data then we need 
	// and only use the top quarter of the frequency spectrum
	// (this part is more visually interesting)

	fftSampleSize = numFloorsPerTower * 4;
	fftRaw = new float[fftSampleSize];
	fftSmooth = new float[fftSampleSize];

	for (int i = 0; i < fftSampleSize; i++)
	{
		fftRaw[i] = 0.0f;
		fftSmooth[i] = 0.0f;
	}
}

//--------------------------------------------------------------
void ofApp::update()
{
	// update sound 

	ofSoundUpdate();

	// update fft

	fftRaw = ofSoundGetSpectrum(fftSampleSize);

	for (int c = 0; c < fftSampleSize; c++)
	{
		fftSmooth[c] *= 0.96f;

		if (fftSmooth[c] < fftRaw[c])
		{
			fftSmooth[c] = fftRaw[c];
		}
	}

	// update disc colors' brightness based on sound 

	for (int t = 0; t < 2; t++)
	{
		for (int f = 0; f < numFloorsPerTower - 1; f++)
		{
			for (int c = 0; c < numCirclesPerFloor; c++)
			{
				towerWalls[t][f][c].clearColors();

				ofColor discColor = wilcoColor;
				float fftAdjust = fftSmooth[f] * 300 + 15;
				discColor.setBrightness(fftAdjust);

				for (int i = 0; i < numVertsPerCircle * 2 + 2; i++)
				{
					if (f != (numFloorsPerTower - 1))
					{
						towerWalls[t][f][c].addColor(discColor);
					}
				}
			}
		}
	}
}

//--------------------------------------------------------------
void ofApp::draw()
{
	MainCamera.begin();

	// draw towers

	for (int t = 0; t < 2; t++)
	{
		for (int f = 0; f < numFloorsPerTower - 1; f++)
		{
			for (int c = 0; c < numCirclesPerFloor; c++)
			{
				towerWalls[t][f][c].draw();
			}
		}
	}

	MainCamera.end();
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key)
{
	switch (key)
	{
	case ' ':
		if (!playing)
		{
			playing = true;
			song.play();
		}
		else
		{
			playing = false;
			song.stop();
		}
		break;
	}
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

}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg) {

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo) {

}
