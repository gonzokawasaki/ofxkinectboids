#include "testApp.h"

//--------------------------------------------------------------
void testApp::setup() {

    ofSetLogLevel(OF_LOG_VERBOSE);

    openNIDevice.setup();//FromXML("openni/config/ofxopenni_config.xml");
    openNIDevice.setLogLevel(OF_LOG_VERBOSE);
    openNIDevice.addDepthGenerator();
    openNIDevice.addImageGenerator();   // comment this out
    openNIDevice.start();
    //openNIDevice.addInfraGenerator(); // and uncomment this to see infrared generator
                                        // or press the 'i' key when running

    verdana.loadFont(ofToDataPath("verdana.ttf"), 24);
}

//--------------------------------------------------------------
void testApp::update(){
    openNIDevice.update();
    
    
}

//--------------------------------------------------------------
void testApp::draw(){

	ofSetColor(255, 255, 255);

   // openNIDevice.drawDebug(); // draws all generators
    //openNIDevice.drawDepth(0, 0);
    //openNIDevice.drawImage(640, 0);

   /* ofSetColor(0, 255, 0);
	string msg = " MILLIS: " + ofToString(ofGetElapsedTimeMillis()) + " FPS: " + ofToString(ofGetFrameRate());
	verdana.drawString(msg, 20, ofGetHeight() - 26);*/

}

//--------------------------------------------------------------
void testApp::exit(){
    openNIDevice.stop();
}

//--------------------------------------------------------------
void testApp::keyPressed(int key){

    switch (key) {
        case 'i':
            if (openNIDevice.isImageOn()){
                openNIDevice.removeImageGenerator();
                openNIDevice.addInfraGenerator();
                break;
            }
            if (openNIDevice.isInfraOn()){
                openNIDevice.removeInfraGenerator();
                openNIDevice.addImageGenerator();
                break;
            }
            break;
        default:
            break;
    }
}

//--------------------------------------------------------------
void testApp::keyReleased(int key){

}

//--------------------------------------------------------------
void testApp::mouseMoved(int x, int y ){

}

//--------------------------------------------------------------
void testApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void testApp::mousePressed(int x, int y, int button){

}

//--------------------------------------------------------------
void testApp::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void testApp::windowResized(int w, int h){

}

/*
 #include "testApp.h"
 #include <iostream>
 #include <GLUT/GLUT.h>
 
 
 
 //--------------------------------------------------------------
 void testApp::setup()
 {
 //ofBackground(0, 0, 0, 1);
 ofSetFrameRate(30);
 ofSetVerticalSync(false);
 ofEnableSmoothing();
 ofEnableAlphaBlending();
 //ofEnableNormalizedTexCoords();
 //ofHideCursor();
 
 glNewList(1, GL_COMPILE);
 glutSolidSphere(1, 40, 40);
 glEndList();
 
 boidNum = 100;
 target = ofVec3f(0, 0, 0);
 
 for (int i = 0; i < boidNum; i++)
 {
 SteeredVehicle v(ofRandom(100)-50, ofRandom(100)-50, ofRandom(100)-50);
 v.maxForce = 0.5f;
 v.inSightDist = 60.0f;
 boids.push_back(v);
 }
 
 cam.setDistance(500);
 
 GLfloat color[] = { 1.0, 0.2, 0.2 };
 
 glEnable(GL_LIGHTING);
 glEnable(GL_LIGHT0);
 glLightfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, color);
 }
 
 //--------------------------------------------------------------
 void testApp::update()
 {
 for (int i = 0; i < boidNum; i++)
 {
 
 
 boids[i].flock(boids);
 boids[i].update();
 boids[i].wrap(300, 300, 300);
 }
 }
 
 //--------------------------------------------------------------
 void testApp::draw()
 {
 glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
 glEnable(GL_DEPTH_TEST);
 
 cam.begin();
 
 for (int i = 0; i < boidNum; i++)
 {
 glPushMatrix();
 glTranslatef(boids[i].position.x, boids[i].position.y, boids[i].position.z);
 
 GLfloat color[] = { 0.8, 0.2, 0.2, 1.0 };
 
 glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, color);
 glCallList(1);
 glPopMatrix();
 }
 
 cam.end();
 }
 
 //--------------------------------------------------------------
 void testApp::keyPressed(int key){
 
 }
 
 //--------------------------------------------------------------
 void testApp::keyReleased(int key){
 
 }
 
 //--------------------------------------------------------------
 void testApp::mouseMoved(int x, int y ){
 
 }
 
 //--------------------------------------------------------------
 void testApp::mouseDragged(int x, int y, int button){
 
 }
 
 //--------------------------------------------------------------
 void testApp::mousePressed(int x, int y, int button){
 
 }
 
 //--------------------------------------------------------------
 void testApp::mouseReleased(int x, int y, int button){
 
 }
 
 //--------------------------------------------------------------
 void testApp::windowResized(int w, int h){
 
 }
 
 //--------------------------------------------------------------
 void testApp::gotMessage(ofMessage msg){
 
 }
 
 //--------------------------------------------------------------
 void testApp::dragEvent(ofDragInfo dragInfo){
 
 }*/
