#include "ObjCollection.h"

//--------------------------------------------------------------
ObjCollection::ObjCollection() {
    gui.setup("MODEL COLLECTION","", ofGetScreenWidth()-220, 10);//ofGetWidth()-230
    gui.add(chooseBut.setup("USE THIS MODEL"));
    gui.add(backBut.setup("BACK TO EDITOR"));
    gui.add(saveModel.setup("SAVE MODEL CONFIG"));

    saveModel.addListener(this, &ObjCollection::setSaveModel);
    chooseBut.addListener(this, &ObjCollection::setChooseBut);
    backBut.addListener(this, &ObjCollection::setBackBut);

    ofFile filExt;
    filExt.open(ofToDataPath("extensions"), ofFile::ReadWrite, false);
    ofBuffer buff = filExt.readToBuffer();
    vector<string> ext = ofSplitString(buff.getText(),",");
    string elementAssimp[ext.size()];
    for( int i = 0; i < ext.size(); i++ ){
        elementAssimp[i]=ext[i];
    }

    for( int i = 0; i < ext.size(); i++ ){
        modelExtensions.push_back(elementAssimp[i]);
        modelExtensions.push_back(ofToLower(elementAssimp[i]));
    }
}

//--------------------------------------------------------------
void ObjCollection::setSaveModel(){
    cout<<"SAVE MODEL "<<"id-model:"<<thisModel<<endl;
    for( int i = 0; i < nameModel.size(); i++ ){
        vector<string> nome = ofSplitString(nameModel[i], ".");
        float scale = models[thisModel]->scale;
        ofVec3f rotat = models[thisModel]->position;
        ofVec3f posis = models[thisModel]->rotation;
        save.saveConfModel(thisModel, nome[0], scale, rotat, posis);
    }
}

//--------------------------------------------------------------
void ObjCollection::loadBootData(string path) {
    ofDirectory dir(path);
    for(int j = 0; j < modelExtensions.size(); j++){
        dir.allowExt(modelExtensions[j]);
        dir.allowExt(ofToLower(modelExtensions[j]));
    }
    dir.listDir();
    for(int i = 0; i < dir.numFiles(); i++){
        ofLogNotice(dir.getPath(i));
        nameModel.push_back(ofFilePath::getFileName(dir.getPath(i)));
        addModel(dir.getPath(i));
    }
}

//--------------------------------------------------------------
void ObjCollection::moveFileData(string pathin, string pathout) {
        ofFile result;
        result.copyFromTo(pathin,pathout);
}

//--------------------------------------------------------------
void ObjCollection::setChooseBut() {
    ofSendMessage("MODELID,"+ofToString(thisModel));
}

//--------------------------------------------------------------
void ObjCollection::setBackBut() {
    ofSendMessage("BACK");
}

//--------------------------------------------------------------
void ObjCollection::addModel(string path) {
    //cout << "ADD MODEL " << path << endl;
	Model* pModel=new Model(models.size());
	if(pModel->load(path)){
		models.push_back(pModel);
	}
    _size=200;
    int padding=5;
    for( int i = 0; i < models.size(); i++ ) {
        vecPosition.push_back(ofPoint(XwidthPos,YheightPos));
        XwidthPos=XwidthPos+_size+padding;
        if (XwidthPos>ofGetScreenWidth()-_size) {
            XwidthPos  = 0;
            YheightPos = YheightPos+_size+padding;
        }
        if (YheightPos>ofGetScreenHeight()) {
            XwidthPos = 0;
            YheightPos = 0;
        }
    }
}

//--------------------------------------------------------------
void ObjCollection::checkClick(int x, int y, int button) {
    for(int i=0;i<zones.size();i++) {
        if(zones[i].inside(x, y)) {
            thisModel = i;
        }
    }
}

//--------------------------------------------------------------
void ObjCollection::drawSelector() {
    zones.clear();
    zones.assign(models.size(), ofRectangle());
	for( int i = 0; i < models.size(); i++ ) {
        /*-----------------------------------------*/
		models[i]->preview.draw(vecPosition[i].x, vecPosition[i].y, _size,_size);
        zones[i].set(vecPosition[i].x, vecPosition[i].y, _size,_size);
        ofPushStyle();
        ofNoFill();
        if(thisModel==i) {
            ofSetColor(255,0,0,255);
        }
        else {
            ofSetColor(0,255,0,255);
        }
        ofRect(zones[i]);
        ofDrawBitmapString(ofToString(i), vecPosition[i].x+10, (vecPosition[i].y+10)+10);
        ofPopStyle();
        /*-----------------------------------------*/
    }
    gui.draw();
    if(models.size()>0) {
        models[thisModel]->drawInfo();
        models[thisModel]->drawGui();
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
