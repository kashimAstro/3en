#include "TextureCollection.h"

//--------------------------------------------------------------
TextureCollection::TextureCollection() {
    gui.setup("TEXTURE COLLECTION","", ofGetScreenWidth()-220, 10);//ofGetWidth()-230
    gui.add(chooseBut.setup("USE THIS TEXTURE"));
    gui.add(backBut.setup("BACK TO EDITOR"));
    gui.add(saveTexture.setup("SAVE TEXTURE CONFIG"));

    saveTexture.addListener(this, &TextureCollection::setSaveTexture);
    chooseBut.addListener(this, &TextureCollection::setChooseBut);
    backBut.addListener(this,   &TextureCollection::setBackBut);

    ofFile filExt;
    filExt.open(ofToDataPath("extensions-texture"), ofFile::ReadWrite, false);
    ofBuffer buff      = filExt.readToBuffer();
    vector<string> ext = ofSplitString(buff.getText(),",");
    string elementTexture[ext.size()];
    for( int i = 0; i < ext.size(); i++ ){
        elementTexture[i] = ext[i];
    }
    for( int i = 0; i < ext.size(); i++ ){
        TextureExtensions.push_back(elementTexture[i]);
        TextureExtensions.push_back(ofToLower(elementTexture[i]));
    }
}

//--------------------------------------------------------------
void TextureCollection::setSaveTexture(){
    cout<<"SET SAVE TEXTURE"<<endl;
}

//--------------------------------------------------------------
void TextureCollection::loadBootData(string path) {
    ofDirectory dir(path);
    for(int j = 0; j < TextureExtensions.size(); j++){
        dir.allowExt(TextureExtensions[j]);
        dir.allowExt(ofToLower(TextureExtensions[j]));
    }
    dir.listDir();
    for(int i = 0; i < dir.numFiles(); i++){
        ofLogNotice(dir.getPath(i));
        nameTexture.push_back(ofFilePath::getFileName(dir.getPath(i)));
        addTexture(dir.getPath(i));
    }
}

//--------------------------------------------------------------
void TextureCollection::moveFileData(string pathin, string pathout) {
        ofFile result;
        result.copyFromTo(pathin,pathout);
}

//--------------------------------------------------------------
void TextureCollection::setChooseBut() {
    ofSendMessage("TEXTUREID,"+ofToString(thisTexture));
}

//--------------------------------------------------------------
void TextureCollection::setBackBut() {
    ofSendMessage("BACK");
}

//--------------------------------------------------------------
void TextureCollection::addTexture(string path) {
	Texture* pTexture=new Texture(textures.size());
	if(pTexture->load(path)){
    		textures.push_back(pTexture);
	}
    _size=200;
    int padding=5;
    for( int i = 0; i < textures.size(); i++ ) {
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
void TextureCollection::checkClick(int x, int y, int button) {
    for(int i=0;i<zones.size();i++) {
        if(zones[i].inside(x, y)) {
            thisTexture = i;
        }
    }
}

//--------------------------------------------------------------
void TextureCollection::drawSelector() {
    zones.clear();
    zones.assign(textures.size(), ofRectangle());
	for( int i = 0; i < textures.size(); i++ ) {
        /*-----------------------------------------*/
		textures[i]->preview.draw(vecPosition[i].x, vecPosition[i].y, _size,_size);
        zones[i].set(vecPosition[i].x, vecPosition[i].y, _size,_size);
        ofPushStyle();
        ofNoFill();
        if(thisTexture==i) {
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
    if(textures.size()>0) {
        textures[thisTexture]->drawInfo();
        textures[thisTexture]->drawGui();
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
