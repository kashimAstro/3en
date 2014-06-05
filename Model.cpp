#include "Model.h"

//--------------------------------------------------------------
Model::Model(){

}

Model::Model(int _ID){
	ID = _ID;
    model=new ofxAssimpModelLoader();
    gui.setup("MODEL "+ofToString(ID), "", ofGetScreenWidth()-220, ofGetScreenHeight()/2);
    gui.add(scale.set("SCALE", 1, 0, 50));
    gui.add(position.set("POSITION", ofVec3f(0,0,0), ofVec3f(-1000,-1000,-5000), ofVec3f(1000,1000,5000)));
    gui.add(rotation.set("ROTATION", ofVec3f(0,0,0), ofVec3f(-360,-360,-360), ofVec3f(360,360,360)));
    scale.addListener(this, &Model::setScale);
    position.addListener(this, &Model::setPosition);
    rotation.addListener(this, &Model::setRotation);
    restore.restoreConfModel(ID,""); /* il nome */
    scale    = restore.Mscale;
    position = ofVec3f(restore.MrotX,restore.MrotY,restore.MrotZ);
    rotation = ofVec3f(restore.MposX,restore.MposY,restore.MposZ);
    cout<<"costruttore Model:"<<ID<<endl;
}

//--------------------------------------------------------------
void Model::setScale(float& var) {
    drawPreview();
}

//--------------------------------------------------------------
void Model::setPosition(ofVec3f& var) {
    drawPreview();
}

//--------------------------------------------------------------
void Model::setRotation(ofVec3f& var) {
    drawPreview();
}

//--------------------------------------------------------------
void Model::drawEditor(ofParameter<bool> doWire){
	/* drawEditor */
	ofPushMatrix();
	ofTranslate(position);
	ofRotateX(rotation->x);
	ofRotateY(rotation->y);
	ofRotateZ(rotation->z);
	ofScale(scale, scale, scale);
	if(doWire) {
        model->drawWireframe();
	}
	else if(!doWire) {
        model->drawFaces();
	}
	ofPopMatrix();
}

//--------------------------------------------------------------
void Model::drawPlayer(){
	/* drawPlayer */
}

//--------------------------------------------------------------
void Model::drawInfo() {
    ofMesh me = model->getMesh(0);
    ofDrawBitmapString("Num Vertices: "+ofToString(me.getNumVertices()*model->getNumMeshes()),10,ofGetScreenHeight()-180);
    ofDrawBitmapString("Animation setting: "+ofToString(model->hasAnimations()),10,ofGetScreenHeight()-160);
    ofDrawBitmapString("Count Animation: "  +ofToString(model->getAnimationCount()),10,ofGetScreenHeight()-140);
 	ofDrawBitmapString("Model position: X:"  +ofToString(model->getPosition().x)+" Y:"+ofToString(model->getPosition().y),10,ofGetScreenHeight()-120);
	ofDrawBitmapString("Model Scene Center: X:"  +ofToString(model->getSceneCenter().x)+" Y:"+ofToString(model->getSceneCenter().y)+" Z:"+ofToString(model->getSceneCenter().z),10,ofGetScreenHeight()-100);
	ofDrawBitmapString("Model Normalized Scale:"  +ofToString(model->getNormalizedScale()),10,ofGetScreenHeight()-80);
	ofDrawBitmapString("Model get Scale: X:"  +ofToString(model->getScale().x)+" Y:"+ofToString(model->getScale().y)+" Z:"+ofToString(model->getScale().z),10,ofGetScreenHeight()-60);
	ofDrawBitmapString("Model Num Mesh: "  +ofToString(model->getNumMeshes()),10,ofGetScreenHeight()-40);
	//int     getNumRotations();	       // returns the no. of applied rotations
	//ofPoint getRotationAxis(int which);  // gets each rotation axis
	//float   getRotationAngle(int which); // gets each rotation angle
}

//--------------------------------------------------------------
void Model::drawGui() {
    gui.draw();
}

//--------------------------------------------------------------
/* resampleModel */
void Model::resampleModel(){
	if(model->hasMeshes()){
		//for( int x = 0; x < model->getNumMeshes(); x++ ) {/* problemi con il numero delle mesh presi dalla model ??*/
			ofMesh mesh = model->getMesh(0);
			vector<ofVec3f> vertMesh = mesh.getVertices();
			vector<ofMeshFace> triangles = mesh.getUniqueFaces();
			if(vertMesh.size()>0){
				int stepFace=6;
				ofVec3f faceNormal;
				lowPoly.clear();
				lowPoly.setMode(OF_PRIMITIVE_TRIANGLES);
				for(int i = 0; i < triangles.size(); i+=stepFace) {
					faceNormal = triangles[i].getFaceNormal();
					for(int j = 0; j < 3; j++ ) {
						triangles[i].setVertex( j, triangles[i].getVertex(j) );
						lowPoly.addVertex  ( triangles[i].getVertex(j) );
						lowPoly.addNormal  ( faceNormal );
						lowPoly.addTexCoord( ofVec2f(triangles[i].getVertex(j).x,triangles[i].getVertex(j).y) );
					}
				}
			}
		//}
        }
}

//--------------------------------------------------------------
void Model::drawPreview(){
	preview.allocate(ofGetWidth(),ofGetHeight(),GL_RGBA);
	preview.begin();
    ofClear(0,0,0,255);
    ofScale(scale,scale,scale);
    ofTranslate(position);
    ofRotateX(rotation->x);
    ofRotateY(rotation->y);
    ofRotateZ(rotation->z);
//    ofTranslate(100,100,100);
//    ofRotateX(160);
//    ofRotateY(-160);
//    model->draw(OF_MESH_WIREFRAME);
//  	model->draw(OF_MESH_WIREFRAME);
    model->draw(OF_MESH_FILL);
	preview.end();
}

//--------------------------------------------------------------
/* drawLowPoly */
void Model::drawLowPoly(){
}

//--------------------------------------------------------------
/* load */
bool Model::load(string path){
	model->loadModel(path);
	ofPoint prvSize=model->getSceneMax();/*ma che re'???*/
//	preview.allocate(200,200,GL_RGBA);
    drawPreview();
    resampleModel();
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
