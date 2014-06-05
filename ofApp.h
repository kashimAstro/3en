#ifndef HEADER_TESTAPP
#define HEADER_TESTAPP

#pragma once

#include "ofMain.h"

#include "World.h"
#include "Player.h"
#include "BaseObj.h"
#include "Camera.h"
#include "ObjCollection.h"
#include "TextureCollection.h"

class ofApp : public ofBaseApp{

public:

    enum MODE { EDITOR, GAME, MODBROWSE, MODEDIT, TEXBROWSE };
    enum TYPE { PLAYER, BASEOBJ };
    enum FILETYPE { MODEL };

    void setup();
    void update();
    void draw();

    void keyPressed(int key);
    void keyReleased(int key);
    void mouseMoved(int x, int y );
    void mouseDragged(int x, int y, int button);
    void mousePressed(int x, int y, int button);
    void mouseReleased(int x, int y, int button);
    void windowResized(int w, int h);
    void dragEvent(ofDragInfo dragInfo);
    void gotMessage(ofMessage msg);

    MODE mode;
    int W,H;

    vector<World*> worlds;
    vector<Player*> players;
    vector<BaseObj*> objects;
    vector<Camera*> cameras;

    int thisCamera;

    void drawGame();

    ofEasyCam camEditor;

    // GLOBAL GUI
    ofxPanel global;
    ofxButton addWorld;
    ofxButton addPlayer;
    ofxButton addObject;
    ofxButton addCamera;
    ofxButton showModelBrowse;
    ofxButton save;
    ofxButton chooseFile;
    ofxButton showTextureBrowse;

    void setShowTexture();
    void setChooseFile();
    void setAddWorld();
    void setAddPlayer();
    void setAddObject();
    void setSave();
    void setAddCamera();
    void setShowModel();
    // END

    // SCENE EDITOR VIEW
    bool moveCam;
    bool sceneMoveCam;

    ofxPanel uiEdit;
    ofParameter<bool> rotate;
    ofParameter<ofVec2f> rotEditor;
    ofParameter<bool> zoompan;
    ofParameter<ofVec3f> zoomPanEditor;
    int prevX;
    int prevY;
    // END

    // ELEMENTS GUI
    ofxPanel worldsGui;
    vector<ofParameter<bool> > worldsBut;

    ofxPanel playersGui;
    vector<ofParameter<bool> > playersBut;

    ofxPanel objectsGui;
    vector<ofParameter<bool> > objectsBut;

    ofxPanel camerasGui;
    vector<ofParameter<bool> > camerasBut;

    ofxPanel controllersGui;
    vector<ofParameter<bool> > controllersBut;
    void resetGui();
    // END

    // MODEL COLLECTION
    ObjCollection objCollection;
    TextureCollection textureCollection;
    Player* needModPlayer;
    BaseObj* needModBaseObj;
    TYPE needType;
    // END

    // FILE UTILS
    void getFileTypeModel(string pathin);
    void getFileTypeTexture(string pathin);
    vector<string> modelExtensions;
    vector<string> textureExtensions;
    // END
};

#endif // header guard
