#ifndef _TEST_APP
#define _TEST_APP

#pragma once

#include "ofMain.h"
#include "ofxBoids.h"
#include "ofxOpenNI.h"
#include "ofMain.h"
#include "ofx3DModelLoader.h"

class testApp : public ofBaseApp{

public:
	void setup();
	void update();
	void draw();
    void exit();

    ofTrueTypeFont verdana;
    
	ofxOpenNI openNIDevice;
    
  
    void keyPressed  (int key);
    void keyReleased(int key);
    void mouseMoved(int x, int y );
    void mouseDragged(int x, int y, int button);
    void mousePressed(int x, int y, int button);
    void mouseReleased(int x, int y, int button);
    void windowResized(int w, int h);
        
    
    ofEasyCam cam;
    
    int boidNum;
    int depthiterate;
    ofVec3f target;
    ofVec3f fleefrom; //my var for the boids evading input
    bool runaway;
    vector<SteeredVehicle> boids;
    vector<ofVec3f>    oldVectors;
    vector<ofVec3f>    tailVectors;
    
    ofx3DModelLoader fishheadmodel;

    
};

#endif

