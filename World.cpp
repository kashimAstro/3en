#include "World.h"

//--------------------------------------------------------------
World::World(int _ID) {
    ID = _ID;

    gui.setup("WORLD "+ofToString(ID)+" SETUP", "", ofGetWidth()-740, (70*ID)+10);
    gui.add(enabled.set("ENABLED", true));
    gui.add(hasTerrain.set("DO TERRAIN", false));
    gui.add(hasSky.set("DO SKYBOX", false));

    hasTerrain.addListener(this, &World::setHasTerrain);
    hasSky.addListener(this,     &World::setHasSky);

    terrainGui.setName("TERRAIN SETUP");
    terrainGui.add(enabledTer.set("RENDER TERRAIN", true));
    terrainGui.add(terPlane.set("PLANE", true));
    terrainGui.add(terSphere.set("SPHERE", false));
    terrainGui.add(terIco.set("ICO", false));
    terrainGui.add(terWire.set("WIREFRAME",false));

    skyGui.setName("SKYBOX SETUP");
    skyGui.add(enabledSky.set("RENDER SKYBOX", true));
    skyGui.add(skySphere.set("SPHERE", true));
    skyGui.add(skyCube.set("CUBE", false));
    skyGui.add(skyWire.set("WIREFRAME",false));

    skyGui.add(skySize.set("SKYBOX SIZE",2000,1,5000));
    skyGui.add(skyRes.set("SKYBOX RESOLUTION",2000,1,5000));

    _path="default/skybox/sky.jpg"; /* -- */
    ofDisableArbTex();
    sky.loadImage(_path);

    plane.set(5000, 5000);
    sphere.setRadius(800);
    ico.setRadius(800);

    sphereSky.setRadius(10000);
    cube.set(2000);
}

//--------------------------------------------------------------
void World::genBase() {
    hasTerrain.removeListener(this, &World::setHasTerrain);
    hasSky.removeListener(this, &World::setHasSky);
    gui.clear();
    gui.add(enabled.set("ENABLED", enabled));
    gui.add(hasTerrain.set("DO TERRAIN", hasTerrain));
    gui.add(hasSky.set("DO SKYBOX", hasSky));
    hasTerrain.addListener(this, &World::setHasTerrain);
    hasSky.addListener(this, &World::setHasSky);
}

//--------------------------------------------------------------
void World::setHasSky(bool& var) {
    hasSky = var;
	//cout<<"enter sky"<<endl;
    if(var) {
        genBase();
        if(hasTerrain) {
           gui.add(terrainGui);
        }
        gui.add(skyGui);
	//cout<<"true sky"<<endl;
    }
    else {
        genBase();
        if(hasTerrain) {
           gui.add(terrainGui);
        }
	//cout<<"false sky"<<endl;
    }
}

//--------------------------------------------------------------
void World::setHasTerrain(bool& var) {
    hasTerrain = var;
	//cout<<"enter terrain"<<endl;
    if(var) {
        genBase();
        gui.add(terrainGui);
        if(hasSky) {
           gui.add(skyGui);
        }
	//cout<<"true terrain"<<endl;
    }
    else {
        genBase();
        if(hasSky) {
           gui.add(skyGui);
        }
	//cout<<"false terrain"<<endl;
    }
}

//--------------------------------------------------------------
void World::sphereRadius(){
    sphereSky.setRadius(skySize);
    cube.set(skySize);
}

//--------------------------------------------------------------
void World::sphereResolution(){
    sphereSky.setResolution(skyRes);
    cube.setResolution(skyRes);
}


//--------------------------------------------------------------
void World::drawGui() {
    if(enabledGui) {
      gui.draw();
    }
}

//--------------------------------------------------------------
void World::drawEditor() {
  	if(enabled) {
  		if(enabledSky){
			ofPushMatrix();
			ofSetColor(255);
			//sky.bind();
            if(skySphere)
                sphereSky.drawWireframe();
            if(skyCube)
                cube.drawWireframe();
			//sky.unbind();
			ofPopMatrix();
		}

		if(enabledTer){
			ofPushMatrix();
			ofPushStyle();
			ofSetColor(255,0,0);
			ofRotateX(92);
			if(terWire){
				if(terPlane)
					plane.drawWireframe();
				if(terSphere)
					sphere.drawWireframe();
				if(terIco)
					ico.drawWireframe();
			}
			else{
				if(terPlane)
					plane.draw();
				if(terSphere)
					sphere.draw();
				if(terIco)
					ico.draw();
			}
			ofPopStyle();
			ofPopMatrix();
		}
	}
}

//--------------------------------------------------------------
void World::drawPlayer() {
	if(enabled) {
		if(enabledSky){
			ofPushMatrix();
			ofSetColor(255);
			sky.bind();
			if(skyWire) {
				if(skySphere)
					sphereSky.drawWireframe();
				if(skyCube)
					cube.drawWireframe();
			}else{
				if(skySphere)
					sphereSky.draw();
				if(skyCube)
					cube.draw();
			}
			sky.unbind();
			ofPopMatrix();
		}

		if(enabledTer){
			ofPushMatrix();
			ofSetColor(255,0,0);
			ofRotateX(90);
			if(terWire){
				if(terPlane)
					plane.drawWireframe();
				if(terSphere)
					sphere.drawWireframe();
				if(terIco)
					ico.drawWireframe();
			}
			else{
				if(terPlane)
					plane.draw();
				if(terSphere)
					sphere.draw();
				if(terIco)
					ico.draw();
			}
			ofPopMatrix();
		}
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
