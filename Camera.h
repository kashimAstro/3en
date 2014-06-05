#ifndef HEADER_CAMERA
#define HEADER_CAMERA

//
//  Camera.h
//  3ngine
//
//  Created by gh00st on 5/26/14.
//
//

#ifndef ___ngine__Camera__
#define ___ngine__Camera__

#include "ofMain.h"
#include "ofxGui.h"

class Camera {

public:
    Camera(int ID);

    int ID;

    ofxPanel gui;
    //ofParameter<bool> enabled;
    ofParameter<bool> doPreview;
    ofParameter<bool> enabledGui;

    void drawGui();
    void drawEditor();
    void drawPlayer();

    ofEasyCam camera;
    ofFbo preview;
    void begin();
    void end();
};

#endif /* defined(___ngine__Camera__) */

#endif // header guard
