//
//
//  3ngine

#ifndef ___ngine__World__
#define ___ngine__World__

#include "ofMain.h"
#include "ofxGui.h"

class World {

public:
    World(int ID);

    int ID;
    string _path;
    ofImage sky;

    // GLOBAL GUI
    ofxPanel gui;
    ofParameter<bool> enabled;
    ofParameter<bool> hasTerrain;
    ofParameter<bool> hasSky;
    void setHasTerrain(bool& var);
    void setHasSky(bool& var);

    void genBase();
    // END

    // TERRAIN GUI
    ofParameterGroup terrainGui;
    ofParameter<bool> enabledTer;
    ofParameter<bool> terPlane;
    ofParameter<bool> terSphere;
    ofParameter<bool> terIco;
    ofParameter<bool> terWire;
    //ofParameter<int>  terSize;
    void setTerType();
    // END

    // TERRAIN
    ofPlanePrimitive plane;
    ofSpherePrimitive sphere;
    ofIcoSpherePrimitive ico;
    ofSpherePrimitive sphereSky;
    ofBoxPrimitive cube;
    void sphereRadius();
    void sphereResolution();
    // END

    // SKYBOX GUI
    ofParameterGroup skyGui;
    ofParameter<bool> enabledSky;
    ofParameter<bool> skySphere;
    ofParameter<bool> skyCube;
    ofParameter<bool> skyWire;
    ofParameter<int>  skySize;
    ofParameter<int>  skyRes;
    // END

    ofParameter<bool> enabledGui;

    void drawGui();
    void drawEditor();
    void drawPlayer();
};

#endif /* defined(___ngine__World__) */
