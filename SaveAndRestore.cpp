#include "SaveAndRestore.h"

SaveRestore::SaveRestore(){

}

void SaveRestore::saveConfModel(int id, string nome, float scale, ofVec3f rotat, ofVec3f posis){
    /* scale */
    modelSetting.setValue("settings:scale", scale);

    /* rotazione */
    modelSetting.setValue("settings:rotateX", rotat.x);
    modelSetting.setValue("settings:rotateY", rotat.y);
    modelSetting.setValue("settings:rotateZ", rotat.z);

    /* position */
    modelSetting.setValue("settings:positionX", posis.x);
    modelSetting.setValue("settings:positionY", posis.y);
    modelSetting.setValue("settings:positionZ", posis.z);
    modelSetting.saveFile("save/model/"+ofToString(id)+".xml");
}

void SaveRestore::restoreConfModel(int id, string nome){
    modelSetting.loadFile("save/model/"+ofToString(id)+".xml");

    /* scale */
    Mscale = modelSetting.getValue("settings:scale",0.0);

    /* rotazione */
    MrotX = modelSetting.getValue("settings:rotateX",0.0);
    MrotY = modelSetting.getValue("settings:rotateY",0.0);
    MrotZ = modelSetting.getValue("settings:rotateZ",0.0);

    /* position */
    MposX = modelSetting.getValue("settings:positionX",0.0);
    MposY = modelSetting.getValue("settings:positionY",0.0);
    MposZ = modelSetting.getValue("settings:positionZ",0.0);
}
