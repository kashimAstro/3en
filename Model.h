#ifndef HEADER_MODEL
#define HEADER_MDOEL

#pragma once

#ifndef ___ngine__Model__
#define ___ngine__Model__


#include "ofMain.h"
#include "ofxAssimpModelLoader.h"
#include "ofxGui.h"
#include "SaveAndRestore.h"

class Model {

public:
    Model();
	Model(int ID);

	int ID;

	bool load(string path);
	void drawEditor(ofParameter<bool> doWire);
	void drawPlayer();
	void drawPreview();
	void drawLowPoly();
	void resampleModel();

	void drawInfo();
	void drawGui();

	ofxPanel gui;
	ofParameter<float> scale;
	ofParameter<ofVec3f> position;
	ofParameter<ofVec3f> rotation;
	void setScale(float& var);
	void setPosition(ofVec3f& var);
	void setRotation(ofVec3f& var);

	ofxAssimpModelLoader* model;
	ofVboMesh lowPoly;
	ofFbo preview;
	//vector<ofFbo> storageFbo;
	SaveRestore restore;
	int XwidthPos,YheightPos,counter;
};
#endif /* defined(___ngine__Model__) */

#endif // header guard
