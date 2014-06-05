#include "Texture.h"

//--------------------------------------------------------------
Texture::Texture(int _ID){
	ID = _ID;

	image=new ofImage();
	gui.setup("IMAGE "+ofToString(ID), "", ofGetScreenWidth()-220, ofGetScreenHeight()/2);//
	gui.add(scale.set("SCALE", 1, 0, 50));
	gui.add(position.set("POSITION", ofVec3f(0,0,0), ofVec3f(-1000,-1000,-5000), ofVec3f(1000,1000,5000)));
	gui.add(rotation.set("ROTATION", ofVec3f(0,0,0), ofVec3f(-360,-360,-360), ofVec3f(360,360,360)));
    scale.addListener(this,    &Texture::setScale);
    position.addListener(this, &Texture::setPosition);
    rotation.addListener(this, &Texture::setRotation);
}

//--------------------------------------------------------------
void Texture::setScale(float& var) {
    drawPreview();
}

//--------------------------------------------------------------
void Texture::setPosition(ofVec3f& var) {
    drawPreview();
}

//--------------------------------------------------------------
void Texture::setRotation(ofVec3f& var) {
    drawPreview();
}

//--------------------------------------------------------------
void Texture::drawEditor(){
	/* drawEditor */
	ofPushMatrix();
	ofTranslate(position);
	ofRotateX(rotation->x);
	ofRotateY(rotation->y);
	ofRotateZ(rotation->z);
	ofScale(scale, scale, scale);
	image->draw(0,0);
	ofPopMatrix();
}

//--------------------------------------------------------------
void Texture::drawPlayer(){
	/* drawPlayer */
}

//--------------------------------------------------------------
void Texture::drawInfo() {
}

//--------------------------------------------------------------
void Texture::drawGui() {
    gui.draw();
}

//--------------------------------------------------------------
void Texture::drawPreview(){
	preview.allocate(ofGetWidth(),ofGetHeight(),GL_RGBA);
	preview.begin();
    ofClear(0,0,0,255);
    ofScale(scale,scale,scale);
    ofTranslate(position);
    ofRotateX(rotation->x);
    ofRotateY(rotation->y);
    ofRotateZ(rotation->z);
    image->draw(0,0);
	preview.end();
}

//--------------------------------------------------------------
/* load */
bool Texture::load(string path){
    cout<<"Path texture:::::"<<path<<endl;
	image->loadImage(path);
    drawPreview();
	return true;
}
/**/
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
//--------------------------------------------------------------
