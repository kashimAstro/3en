#ifndef HEADER_OBJCOLLECTION
#define HEADER_OBJCOLLECTION

#pragma once

#include "ofMain.h"
#include "ofxAssimpModelLoader.h"
#include "Model.h"
#include "ofxGui.h"
#include "SaveAndRestore.h"

class ObjCollection {

public:
    ObjCollection();
    void loadBootData(string path);
    void moveFileData(string pathin,string pathout);
	void addModel(string path);
	vector<Model*> models;

    ofxPanel gui;
    ofxButton chooseBut;
    ofxButton backBut;
    ofxButton saveModel;
    void setSaveModel();
    void setChooseBut();
    void setBackBut();

    ofParameter<bool> enabledGui;

    void drawGui();
    void drawEditor();
    void drawPlayer();

    int thisModel;
    Model* getModelRef(int id);
    void checkClick(int x, int y, int button);
    void drawSelector();

    int XwidthPos,YheightPos;
    vector<ofRectangle> zones;
    int _size,_pos;
    vector<ofPoint> vecPosition;

    SaveRestore save;
    vector<string> modelExtensions;
    vector<string> nameModel;
};

#endif // header guard
