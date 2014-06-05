#ifndef HEADER_BASEOBJ
#define HEADER_BASEOBJ

#ifndef ___ngine__BaseObj__
#define ___ngine__BaseObj__

#include "ofMain.h"
#include "ofxGui.h"
#include "Model.h"
#include "Texture.h"

class BaseObj {

public:
    BaseObj(int ID);

    int ID;
    Model* model;
    Texture* texture;

    bool gotModel,gotTexture;

    ofxPanel gui;
    ofParameter<bool> enabled;
    ofxButton chooseModel;
    ofxButton chooseTexture;
    ofParameter<bool> doWire;
    void setChooseModel();
    void setChooseTexture();

    ofParameterGroup transformGui;
    ofParameter<ofVec3f> position;
    ofParameter<ofVec3f> rotation;
    ofParameter<float> scale;

    ofParameter<bool> enabledGui;

    void drawGui();
    void drawEditor();
    void drawPlayer();
};

#endif /* defined(___ngine__BaseObj__) */

#endif // header guard
