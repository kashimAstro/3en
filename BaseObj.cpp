#include "BaseObj.h"

//--------------------------------------------------------------
BaseObj::BaseObj(int _ID) {
    ID = _ID;
    model = new Model();

    gui.setup("OBJECT "+ofToString(ID)+" SETUP", "", ofGetWidth()-230, (70*ID)+10);
    gui.add(enabled.set("ENABLED", false));
    gui.add(chooseModel.setup("CHOOSE MODEL"));
    gui.add(chooseTexture.setup("CHOOSE TEXTURE"));
    gui.add(doWire.set("WIREFRAME", true));

    chooseModel.addListener(this, &BaseObj::setChooseModel);
    chooseTexture.addListener(this, &BaseObj::setChooseTexture);

    transformGui.setName("MATRIX TRANSFORM");
    transformGui.add(scale.set("SCALE", 1, -10, 10));
    transformGui.add(position.set("POSITION", ofVec3f(0,0,0), ofVec3f(-10000,-10000,-10000), ofVec3f(10000,10000,10000)));
    transformGui.add(rotation.set("ROTATION", ofVec3f(0,0,0), ofVec3f(-360,-360,-360), ofVec3f(360,360,360)));

    gui.add(transformGui);
    gotModel   = false;
    gotTexture = false;
}

//--------------------------------------------------------------
void BaseObj::setChooseModel() {
    ofSendMessage("SETMODEL,BASEOBJ,"+ofToString(ID));
    gotModel = true;
}

//--------------------------------------------------------------
void BaseObj::setChooseTexture() {
    ofSendMessage("SETTEXTURE,BASEOBJ,"+ofToString(ID));
    gotTexture = true;
}

//--------------------------------------------------------------
void BaseObj::drawGui() {
    if(enabledGui) {
        gui.draw();
        model->preview.draw(gui.getPosition().x, gui.getPosition().y+gui.getHeight()+5, gui.getWidth(), gui.getWidth());
        model->drawGui();
        int pos=5;
        if(model->preview.isAllocated()){
                pos=205;
        }
        texture->preview.draw(gui.getPosition().x, gui.getPosition().y+gui.getHeight()+pos, gui.getWidth(), gui.getWidth());
    }
}

//--------------------------------------------------------------
void BaseObj::drawEditor() {
    if(gotModel) {
        ofPushMatrix();
        ofTranslate(position);
        ofRotateX(rotation->x);
        ofRotateY(rotation->y);
        ofRotateZ(rotation->z);
        ofScale(scale, scale, scale);
        model->drawEditor(doWire);
        ofPopMatrix();
    }
    if(gotTexture){
        ofPushMatrix();
        ofTranslate(position);
        ofRotateX(rotation->x);
        ofRotateY(rotation->y);
        ofRotateZ(rotation->z);
        ofScale(scale, scale, scale);
        texture->drawEditor();
        ofPopMatrix();
    }
}

//--------------------------------------------------------------
void BaseObj::drawPlayer() {
    if(enabled) {
        /* */
    }
}

//--------------------------------------------------------------
//--------------------------------------------------------------
//--------------------------------------------------------------
//--------------------------------------------------------------
//--------------------------------------------------------------
//--------------------------------------------------------------
//--------------------------------------------------------------
//--------------------------------------------------------------
//--------------------------------------------------------------
//--------------------------------------------------------------
//--------------------------------------------------------------
//--------------------------------------------------------------
//--------------------------------------------------------------
//--------------------------------------------------------------
//--------------------------------------------------------------
//--------------------------------------------------------------
//--------------------------------------------------------------
//--------------------------------------------------------------
//--------------------------------------------------------------
