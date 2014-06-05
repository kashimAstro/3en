#ifndef HEADER_TEXTURECOLLECTION
#define HEADER_TEXTURECOLLECTION

#pragma once

#include "ofMain.h"
#include "ofxGui.h"
#include "Texture.h"
#include "SaveAndRestore.h"

class TextureCollection {

public:
    TextureCollection();
    void loadBootData(string path);
    void moveFileData(string pathin,string pathout);
	void addTexture(string path);
	vector<Texture*> textures;

    ofxPanel gui;
    ofxButton chooseBut;
    ofxButton backBut;
    ofxButton saveTexture;
    void setSaveTexture();
    void setChooseBut();
    void setBackBut();

    ofParameter<bool> enabledGui;

    void drawGui();
    void drawEditor();
    void drawPlayer();

    int thisTexture;
    Texture* getModelRef(int id);
    void checkClick(int x, int y, int button);
    void drawSelector();

    int XwidthPos,YheightPos;
    SaveRestore save;

    int _size;
    vector<ofPoint> vecPosition;

    vector<ofRectangle> zones;
    vector<string> TextureExtensions;
    vector<string> nameTexture;
};

#endif // header guard
