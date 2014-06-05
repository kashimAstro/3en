#pragma once

#include "ofMain.h"
#include "ofxXmlSettings.h"

class SaveRestore {

public:
    SaveRestore();
    void saveConfModel(int id, string nome, float scale, ofVec3f rotat, ofVec3f posis);
    void restoreConfModel(int id, string nome);
    ofxXmlSettings modelSetting;
    float Mscale,MrotX,MrotY,MrotZ,MposX,MposY,MposZ;
};
