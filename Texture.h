#ifndef HEADER_TEXTURE
#define HEADER_TEXTURE

#pragma once

#ifndef ___ngine__Texture__
#define ___ngine__Texture__


#include "ofMain.h"
#include "ofxGui.h"
#include "SaveAndRestore.h"

class Texture {

public:
	Texture(int ID);

	int ID;

	bool load(string path);
	void drawEditor();
	void drawPlayer();
	void drawPreview();

	void drawInfo();
	void drawGui();

	ofxPanel gui;
	ofParameter<float> scale;
	ofParameter<ofVec3f> position;
	ofParameter<ofVec3f> rotation;
	void setScale(float& var);
	void setPosition(ofVec3f& var);
	void setRotation(ofVec3f& var);

	ofImage* image;
	ofFbo preview;
	SaveRestore restore;
};
#endif /* defined(___ngine__Model__) */

#endif // header guard
