#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup()
{
	ofSetFrameRate(30.0);
	ofBackground(199, 179, 149);
	ofSetBackgroundAuto(true);
	ofSetVerticalSync(true);

	// set up camera

	MainCamera.setGlobalPosition(glm::vec3(0.0f, 1000.0f, -600.0f));
	MainCamera.lookAt(glm::vec3(0, 0, 0));

	// tower 0 

	tower0 = new ofMesh[numDiscsPerTower]; 

	ofPoint start = ofVec3f(0, 0, 0);
	float zStep = towerHeight / numDiscsPerTower;

	ofColor colorDisc = ofColor(0, 0, 0); 
	float rStep = 199 / numDiscsPerTower;
	float gStep = 179 / numDiscsPerTower;
	float bStep = 149 / numDiscsPerTower;

	for (int d = 0; d < numDiscsPerTower; d++)
	{
		// tower 0 is the one off in the distance

		start.set(200, -700, -zStep * d);
		colorDisc.set(ofColor(rStep * d, gStep * d, bStep * d));

		tower0[d].setMode(OF_PRIMITIVE_TRIANGLE_FAN); 
		float circleX, circleY, circleZ; 

		for (int t = 0; t < numVertsPerDisc; ++t)
		{
			float vertAngle = t * TWO_PI / numVertsPerDisc;

			circleX = start.x + baseRadius * cos(vertAngle);
			circleY = start.y + baseRadius * sin(vertAngle);
			circleZ = start.z;

			ofPoint point = ofVec3f(circleX, circleY, circleZ);

			tower0[d].addVertex(point);
			tower0[d].addColor(colorDisc);
		}
	}

	// tower 1

	tower1 = new ofMesh[numDiscsPerTower];

	for (int d = 0; d < numDiscsPerTower; d++)
	{
		// tower 1 is closer and to the right

		start.set(-200, 100, -zStep * d);
		colorDisc.set(ofColor(rStep * d, gStep * d, bStep * d));

		tower1[d].setMode(OF_PRIMITIVE_TRIANGLE_FAN);
		float circleX, circleY, circleZ;

		for (int t = 0; t < numVertsPerDisc; ++t)
		{
			float vertAngle = t * TWO_PI / numVertsPerDisc;

			circleX = start.x + baseRadius * cos(vertAngle);
			circleY = start.y + baseRadius * sin(vertAngle);
			circleZ = start.z;

			ofPoint point = ofVec3f(circleX, circleY, circleZ);

			tower1[d].addVertex(point);
			tower1[d].addColor(colorDisc);
		}
	}
}

//--------------------------------------------------------------
void ofApp::update()
{
	// update build counters

	if (tower0building)
		buildCounter0++; 

	if (tower1building)
		buildCounter1++; 
}

//--------------------------------------------------------------
void ofApp::draw()
{
	MainCamera.begin();

	// tower0

	int discsToBuild = buildCounter0 / 5; 

	if (discsToBuild > numDiscsPerTower)
		discsToBuild = numDiscsPerTower; 

	for (int i = 0; i < discsToBuild; i++)
	{
		tower0[i].draw(); 
	}

	// tower1

	discsToBuild = buildCounter1 / 5;

	if (discsToBuild > numDiscsPerTower)
		discsToBuild = numDiscsPerTower;

	for (int i = 0; i < discsToBuild; i++)
	{
		tower1[i].draw();
	}

	MainCamera.end(); 
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key)
{
	switch (key)
	{
	case ' ':
		if (!tower0building && !tower1building)
		{
			tower0building = true;
		}
		else if (tower0building && !tower1building)
		{
			tower1building = true;
		}
		break;
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

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){ 

}
