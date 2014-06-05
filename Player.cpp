//
//  Player.cpp
//  3ngine
//
//  Created by gh00st on 5/26/14.
//
//

#include "Player.h"

//--------------------------------------------------------------
Player::Player(int _ID) {
    ID = _ID;

    gui.setup("PLAYER "+ofToString(ID)+" SETUP", "", ofGetWidth()-500, (70*ID)+10);
    gui.add(enabled.set("ENABLED", false));
    gui.add(hasBody.set("HAS BODY", false));
    gui.add(showBody.set("SHOW BODY", false));
    gui.add(movePlayer.set("MOVE PLAYER", false));
    gui.add(chooseModel.setup("CHOOSE MODEL"));
    gui.add(chooseTexture.setup("CHOOSE TEXTURE"));
    chooseModel.addListener(this, &Player::setChooseModel);
    chooseTexture.addListener(this, &Player::setChooseTexture);
    gui.add(movementSpeed.set("MOVEMENT SPEED", 7, 0, 100));
    gui.add(startPos.set("START POSITION", ofVec3f(0,0,0), ofVec3f(-10000,-10000,-10000), ofVec3f(10000,10000,10000)));

    model = new Model();

    setPosition(0,0,0);
}

//--------------------------------------------------------------
void Player::setChooseModel() {
    ofSendMessage("SETMODEL,PLAYER,"+ofToString(ID));
}

//--------------------------------------------------------------
void Player::setChooseTexture() {
    ofSendMessage("SETTEXTURE,PLAYER,"+ofToString(ID));
}

//--------------------------------------------------------------
void Player::drawGui() {
    if(enabledGui) {
        gui.draw();
        model->preview.draw(gui.getPosition().x, gui.getPosition().y+gui.getHeight()+5, gui.getWidth(), gui.getWidth());
        model->drawGui();
    }
}

//--------------------------------------------------------------
void Player::customDraw() {
    if(showBody) {
        model->drawEditor(true);
    }
        ofPushStyle();
        ofSetColor(0,255,0,100);
        ofDrawBox(0, 40, 0, 40,80,40);
        ofPopStyle();
}

//--------------------------------------------------------------
void Player::drawEditor() {

    if(movePlayer) {

        ofVec3f forward =  ofVec3f(0,0,1) * getOrientationQuat();
        ofVec3f sideways = ofVec3f(1,0,0) * getOrientationQuat();

        if( ofGetKeyPressed('w') ) setPosition( getPosition() + (-forward * movementSpeed) );
        if( ofGetKeyPressed('s') ) setPosition( getPosition() + ( forward * movementSpeed) );

        if( ofGetKeyPressed('a') ) setPosition( getPosition() + (-sideways * movementSpeed) );
        if( ofGetKeyPressed('d') ) setPosition( getPosition() + ( sideways * movementSpeed) );

        ofPoint mouse = ofPoint(ofGetMouseX(), ofGetMouseY());
        ofPoint mouseVel = mouse - lastMouse;

        pan(mouseVel.x/4);

        lastMouse = mouse;
    }

    draw();

}

//--------------------------------------------------------------
void Player::drawPlayer() {
    if(enabled) {

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
