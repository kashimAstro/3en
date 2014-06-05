#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    ofBackground(0);
    ofSetFrameRate(120);
    mode = EDITOR;
    W=ofGetScreenWidth();
    H=ofGetScreenHeight();

    // GLOBAL GUI
    global.setup("GLOBAL CONTROL","",0,10);
    global.add(addWorld.setup("ADD WORLD"));
    global.add(addPlayer.setup("ADD PLAYER"));
    global.add(addCamera.setup("ADD CAMERA"));
    global.add(addObject.setup("ADD OBJECT"));
    global.add(showModelBrowse.setup("SHOW MODELS BROWSER"));
    global.add(showTextureBrowse.setup("SHOW TEXTURE BROWSER"));
    global.add(save.setup("SAVE ALL"));
    global.add(chooseFile.setup("CHOOSE FILE"));

    chooseFile.addListener(this, &ofApp::setChooseFile);
    addWorld.addListener(this,  &ofApp::setAddWorld);
    addPlayer.addListener(this, &ofApp::setAddPlayer);
    addCamera.addListener(this, &ofApp::setAddCamera);
    addObject.addListener(this, &ofApp::setAddObject);
    save.addListener(this,      &ofApp::setSave);
    showModelBrowse.addListener(this, &ofApp::setShowModel);
    showTextureBrowse.addListener(this, &ofApp::setShowTexture);

    // END

    // ELEMENTS GUI
    worldsGui.setup("WORLDS","",0,global.getHeight()+30);
    playersGui.setup("PLAYERS","",0,worldsGui.getPosition().y+worldsGui.getHeight()+30);
    objectsGui.setup("OBJECTS","",0,playersGui.getPosition().y+playersGui.getHeight()+30);
    camerasGui.setup("CAMERAS","",0,objectsGui.getPosition().y+objectsGui.getHeight()+30);
    // END

    /* debug editor controller */
    moveCam = false;
    camEditor.disableMouseInput();

    sceneMoveCam = false;

    /*
    uiEdit.setup("EDITOR VIEW","",W-220,H-250);
    rotate.set("ROTATE",false);
    uiEdit.add(rotEditor.set("SCENE ROTATION", ofVec2f(0,0), ofVec2f(0,0), ofVec2f(360,360)));
    zoompan.set("ZOOM/PAN",false);
    uiEdit.add(zoomPanEditor.set("SCENE ZOOM/PAN", ofVec3f(0,0,0), ofVec3f(-W*10,-H*10,-10000), ofVec3f(W*10,H*10,10000)));
*/

    /* estensioni model ammesse */
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
    /* estensioni texture ammesse */
    ofFile filExt1;
    filExt1.open(ofToDataPath("extensions-texture"), ofFile::ReadWrite, false);
    ofBuffer buff1 = filExt1.readToBuffer();
    vector<string> ext1 = ofSplitString(buff1.getText(),",");
    string elementTexture1[ext1.size()];
    for( int i = 0; i < ext1.size(); i++ ){
        elementTexture1[i]=ext1[i];
    }
    for( int i = 0; i < ext1.size(); i++ ){
        textureExtensions.push_back(elementTexture1[i]);
        textureExtensions.push_back(ofToLower(elementTexture1[i]));
    }
    // END
    needModBaseObj = new BaseObj(0);
    needModPlayer  = new Player(0);
    objCollection.loadBootData("default/model/");       /* loading modelli */
    textureCollection.loadBootData("default/texture/"); /* loading texture */

    camEditor.setFarClip(100000);
}

//--------------------------------------------------------------
void ofApp::setShowModel() {
    mode = MODBROWSE;
}

//--------------------------------------------------------------
void ofApp::setShowTexture(){
    mode = TEXBROWSE;
}
//--------------------------------------------------------------

//--------------------------------------------------------------
void ofApp::setAddWorld() {
    World* nuWorld = new World(worlds.size());
    worldsGui.add(nuWorld->enabledGui.set("WORLD "+ofToString(worlds.size()), false));
    worlds.push_back(nuWorld);
    playersGui.setPosition(ofPoint(0,worldsGui.getPosition().y+worldsGui.getHeight()+30));
    objectsGui.setPosition(ofPoint(0,playersGui.getPosition().y+playersGui.getHeight()+30));
    camerasGui.setPosition(ofPoint(0,objectsGui.getPosition().y+objectsGui.getHeight()+30));
}

//--------------------------------------------------------------
void ofApp::setAddPlayer() {
    Player* nuPlayer = new Player(players.size());
    playersGui.add(nuPlayer->enabledGui.set("PLAYER "+ofToString(players.size()), false));
    players.push_back(nuPlayer);
    objectsGui.setPosition(ofPoint(0,playersGui.getPosition().y+playersGui.getHeight()+30));
    camerasGui.setPosition(ofPoint(0,objectsGui.getPosition().y+objectsGui.getHeight()+30));
}

//--------------------------------------------------------------
void ofApp::setAddCamera() {
    Camera* nuCamera = new Camera(cameras.size());
    camerasGui.add(nuCamera->enabledGui.set("CAMERA "+ofToString(cameras.size()), false));
    cameras.push_back(nuCamera);
    camerasGui.setPosition(ofPoint(0,objectsGui.getPosition().y+objectsGui.getHeight()+30));
}

//--------------------------------------------------------------
void ofApp::setAddObject() {
    BaseObj* nuObj = new BaseObj(objects.size());
    objectsGui.add(nuObj->enabledGui.set("OBJECT "+ofToString(objects.size()), false));
    objects.push_back(nuObj);
    camerasGui.setPosition(ofPoint(0,objectsGui.getPosition().y+objectsGui.getHeight()+30));
}

//--------------------------------------------------------------
void ofApp::setSave() {
    cout << "ADDWORLD" << endl;
}

/* debug mouse position */
#if defined( TARGET_LINUX )
    void moveMousePointer(int x, int y) {
        Display *dpy;
        Window root_window;
        dpy = XOpenDisplay(0);
        root_window = XRootWindow(dpy, 0);
        XSelectInput(dpy, root_window, KeyReleaseMask);
        XWarpPointer(dpy, None, root_window, 0, 0, 0, 0, x,y);
        XFlush(dpy);
    }
#endif

#if defined( TARGET_OSX )
    void moveMousePointer(int x, int y) {
        /* OSX */
        //CGPoint point;
        //point.y = ofGetWindowPositionY() + ofGetMouseY();
        //point.x = ofGetWindowPositionX() + ofGetWidth()/2;
        //CGWarpMouseCursorPosition(point);
        //CGAssociateMouseAndMouseCursorPosition(true);
    }
#endif


#if defined( TARGET_WIN32 )
    void moveMousePointer(int x, int y) { /* WIN32 */ }
#endif
/* debug mouse position */

//--------------------------------------------------------------
void ofApp::update(){
    ofSetWindowTitle(ofToString(ofGetFrameRate(),0));
    /*debug mouse position */
    #if defined( TARGET_LINUX ) && 1
    if(ofGetMouseX()>=(ofGetScreenWidth()-2))
        moveMousePointer(ofGetScreenWidth()/2,ofGetScreenHeight()/2);
    if(ofGetMouseX()<=(2))
        moveMousePointer(ofGetScreenWidth()/2,ofGetScreenHeight()/2);
    #endif
    /*debug mouse position*/
}

//--------------------------------------------------------------
void ofApp::draw(){
    if(mode==EDITOR) {
        ofBackgroundGradient(100, 0);

//      camEditor.setPosition(zoomPanEditor->x, zoomPanEditor->y, zoomPanEditor->z);
        camEditor.begin();
        ofPushMatrix();

//    	ofRotateX(rotEditor->y);
//     	ofRotateY(rotEditor->x);

        for(int i=0;i<worlds.size();i++) {
        	worlds[i]->drawEditor();
        }
        for(int i=0;i<players.size();i++) {
        	players[i]->drawEditor();
        }
        for(int i=0;i<objects.size();i++) {
        	objects[i]->drawEditor();
        }
        for(int i=0;i<cameras.size();i++) {
        	cameras[i]->drawEditor();
        }
        ofPopMatrix();
        camEditor.end();

        //
        for(int i=0;i<worlds.size();i++) {
            worlds[i]->drawGui();
        }
        for(int i=0;i<players.size();i++) {
            players[i]->drawGui();
        }
        for(int i=0;i<objects.size();i++) {
            objects[i]->drawGui();
        }
        for(int i=0;i<cameras.size();i++) {
            cameras[i]->drawGui();
        }
        //
        if(cameras.size()>0) {
            if(cameras[thisCamera]->doPreview) {
                cameras[thisCamera]->preview.begin();
                ofClear(0,255);
                drawGame();
                cameras[thisCamera]->preview.end();
            }
        }
        //
        global.draw();
        worldsGui.draw();
        playersGui.draw();
        objectsGui.draw();
        camerasGui.draw();
    }
    else if(mode==GAME){
        drawGame();
    }
    else if(mode==MODBROWSE) {
        ofBackgroundGradient(100, 0);
        objCollection.drawSelector();
    }
    else if(mode==TEXBROWSE){
        ofBackgroundGradient(ofColor(0),ofColor(25));
        textureCollection.drawSelector();
    }
}

//--------------------------------------------------------------
void ofApp::drawGame() {
    if(cameras.size()>0) {
        cameras[thisCamera]->begin();
    }
    for(int i=0;i<worlds.size();i++) {
        worlds[i]->drawPlayer();
    }
    for(int i=0;i<players.size();i++) {
        players[i]->drawPlayer();
    }
    for(int i=0;i<objects.size();i++) {
        objects[i]->drawPlayer();
    }
    for(int i=0;i<cameras.size();i++) {
        cameras[i]->drawPlayer();
    }
    if(cameras.size()>0) {
    cameras[thisCamera]->end();
    }
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
    if(key=='f') {
        ofToggleFullscreen();
    }
    else if(key=='q') {
        moveCam = !moveCam;
        if(moveCam) {
            camEditor.enableMouseInput();
            if(cameras.size()>0) {
                cameras[thisCamera]->camera.disableMouseInput();
                sceneMoveCam = false;
            }
        }
        else {
            camEditor.disableMouseInput();
        }
    }
    else if(key=='w') {
        sceneMoveCam = !sceneMoveCam;
        if(sceneMoveCam) {
            camEditor.disableMouseInput();
            moveCam = false;
            if(cameras.size()>0) {
                cameras[thisCamera]->camera.enableMouseInput();
            }
        }
        else {
            if(cameras.size()>0) {
                cameras[thisCamera]->camera.disableMouseInput();
            }
        }
    }
    else if(key==' ') {
        if(mode==EDITOR) {
            mode=GAME;
        }
        else if(mode==GAME) {
            mode=EDITOR;
        }
    }
}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){

}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){

}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button) {
    /*
    int xx;
    int yy;

	if(rotate) {
        xx = rotEditor->x + (prevX - x);
        yy = rotEditor->y + (prevY - y);
        cout << "XX " << xx << " -- " << rotEditor->x << " -- " << (prevX - x) << endl;
        rotEditor.set("SCENE ROTATION", ofVec2f(xx,yy), ofVec2f(0,0), ofVec2f(360,360));
	}
	else if(zoompan) {
        if(button == 2) {
            xx = zoomPanEditor->x + (prevX - x);
            yy = zoomPanEditor->y + (prevY - y);
            zoomPanEditor.set("SCENE ZOOM/PAN", ofVec3f(xx,yy,zoomPanEditor->z), ofVec3f(-W*10,-H*10,-10000), ofVec3f(W*10,H*10,10000));
        }
        else if(button == 0) {
            yy = zoomPanEditor->z + (prevY - y);
            zoomPanEditor.set("SCENE ZOOM/PAN", ofVec3f(zoomPanEditor->x,zoomPanEditor->y,yy), ofVec3f(-W*10,-H*10,-10000), ofVec3f(W*10,H*10,10000));
        }
	}
	prevX = x;
	prevY = y;
    */
}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){
    if(mode==MODBROWSE) {
        objCollection.checkClick(x,y,button);
    }
    if(mode==TEXBROWSE) {
        textureCollection.checkClick(x,y,button);
    }
}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){
    cout << "GOT MSG: " << msg.message << endl;
    vector<string> pieces = ofSplitString(msg.message, ",");
    if(pieces[0]=="SETMODEL") {
        mode = MODBROWSE;
        if(pieces[1]=="PLAYER") {
            needType = PLAYER;
            needModPlayer = players[ofToInt(pieces[2])];
        }
        else if(pieces[1]=="BASEOBJ") {
            needType = BASEOBJ;
            needModBaseObj = objects[ofToInt(pieces[2])];
        }
    }
    else if(pieces[0]=="MODELID") {
        if(needType==PLAYER) {
            needModPlayer->model = objCollection.models[ofToInt(pieces[1])];
        }
        else if(needType==BASEOBJ) {
            needModBaseObj->model = objCollection.models[ofToInt(pieces[1])];
        }
        mode=EDITOR;
    }
    else if(pieces[0]=="TEXTUREID"){
        if(needType==PLAYER) {
            needModPlayer->texture = textureCollection.textures[ofToInt(pieces[1])];
        }
        else if(needType==BASEOBJ) {
            needModBaseObj->texture = textureCollection.textures[ofToInt(pieces[1])];
        }
        mode=EDITOR;
    }
    else if(pieces[0]=="SETTEXTURE") {
        mode=TEXBROWSE;
        if(pieces[1]=="PLAYER") {
          needType = PLAYER;
          needModPlayer = players[ofToInt(pieces[2])];
        }
        else if(pieces[1]=="BASEOBJ") {
            needType = BASEOBJ;
            needModBaseObj = objects[ofToInt(pieces[2])];
        }
    }
    else if(pieces[0]=="BACK") {
        mode=EDITOR;
    }
}

//--------------------------------------------------------------
void ofApp::getFileTypeModel(string pathin) {
    string filein = ofFilePath::getFileName(pathin);
    string pathout= "default/model/"+filein;
    vector<string> extend = ofSplitString(filein, ".");
    for(int i=0;i<modelExtensions.size();i++) {
        if(extend[1]==modelExtensions[i]){
            ofFile file;
            file.open(pathout, ofFile::ReadWrite, false);
            if(file.exists()){
                ofSystemAlertDialog("!!!!! FILE EXISTS !!!!!");
            }
            else{
                objCollection.moveFileData(pathin,pathout);
                objCollection.addModel(pathout);
                objCollection.nameModel.push_back(ofFilePath::getFileName(pathout));
                //cout<<"filein::" <<pathin<<endl;
                //cout<<"fileout::"<<pathout<<endl;
                //cout<<"nonesiste"<<endl;
            }
        }
    }
}

//--------------------------------------------------------------
void ofApp::getFileTypeTexture(string pathin) {
    string filein = ofFilePath::getFileName(pathin);
    string pathout= "default/texture/"+filein;
    vector<string> extend = ofSplitString(filein, ".");
    for(int i=0;i<textureExtensions.size();i++) {
        if(extend[1]==textureExtensions[i]){
            ofFile file;
            file.open(pathout, ofFile::ReadWrite, false);
            if(file.exists()){
                ofSystemAlertDialog("!!!!! FILE EXISTS !!!!!");
            }
            else{
                textureCollection.moveFileData(pathin,pathout);
                textureCollection.addTexture(pathout);
                textureCollection.nameTexture.push_back(ofFilePath::getFileName(pathout));
                //cout<<"filein::" <<pathin<<endl;
                //cout<<"fileout::"<<pathout<<endl;
                //cout<<"nonesiste"<<endl;
            }
        }
    }
}

//--------------------------------------------------------------
void ofApp::setChooseFile() {
    ofFileDialogResult file = ofSystemLoadDialog("add file");
    if (file.bSuccess){
            ofLogNotice("adding file"+file.filePath);
            getFileTypeModel(file.filePath);
            getFileTypeTexture(file.filePath);
    }else {
            ofLogNotice("cancel adding file");
    }
}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo) {
    if(dragInfo.files.size()==1) {
          getFileTypeModel(dragInfo.files[0]);
          getFileTypeTexture(dragInfo.files[0]);
    }
    else {
        ofSystemAlertDialog("!!!!! ONLY ONE FILE !!!!!");
    }
}
