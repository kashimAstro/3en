#ifndef HEADER_PLAYER
#define HEADER_PLAYER

#ifndef ___ngine__Player__
#define ___ngine__Player__

#include "ofMain.h"
#include "ofxGui.h"
#include "Model.h"
#include "Texture.h"

class Player : public ofNode {

public:
    Player(int ID);

    int ID;
    Model* model;
    Texture* texture;

    ofxPanel gui;
    ofParameter<bool> enabled;
    ofParameter<bool> hasBody;
    ofParameter<bool> showBody;
    ofParameter<bool> movePlayer;

    ofParameter<ofVec3f> startPos;

    ofParameter<float> movementSpeed;

    ofxButton chooseModel;
    ofxButton chooseTexture;
    void setChooseModel();
    void setChooseTexture();
    ofParameter<bool> enabledGui;

    void customDraw();
    void drawGui();
    void drawGuiTexture();
    void drawEditor();
    void drawPlayer();

    ofPoint lastMouse;
};

#endif /* defined(___ngine__Player__) */

#endif // header guard
