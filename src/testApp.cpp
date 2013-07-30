#include "testApp.h"
#include <iostream>
#include <GLUT/GLUT.h>






//--------------------------------------------------------------
void testApp::setup() {
    
/* 
   fishheadmodel.loadModel("3dmodel/NewSquirrel.3ds", 3);

    
    fishheadmodel.setRotation(0, 90, 1, 0, 0);
    fishheadmodel.setRotation(1, 270, 0, 0, 1);
    fishheadmodel.setScale(0.9, 0.9, 0.9);
    fishheadmodel.setPosition(0,0, 0);
    
    glEnable (GL_DEPTH_TEST);
    glShadeModel (GL_SMOOTH);
    
    glColorMaterial (GL_FRONT_AND_BACK, GL_DIFFUSE);
    glEnable (GL_COLOR_MATERIAL);
 */
    
    oldVectors.resize( boidNum );
    
    
    fleefrom = ofVec3f(0.0,0.0,100.0);
    
    //ofSetBackgroundAuto(false);


   ofSetLogLevel(OF_LOG_VERBOSE);

    openNIDevice.setup();//FromXML("openni/config/ofxopenni_config.xml");
    openNIDevice.setLogLevel(OF_LOG_VERBOSE);
    openNIDevice.addDepthGenerator();
    openNIDevice.addImageGenerator();   // comment this out
    openNIDevice.setUseDepthRawPixels(true);
    openNIDevice.start();
    //openNIDevice.addInfraGenerator(); // and uncomment this to see infrared generator
                                        // or press the 'i' key when running

    //verdana.loadFont(ofToDataPath("verdana.ttf"), 24);
    
    
    
    // setup for boids below
    
    ofBackground(0, 30, 80, 0);
    ofSetFrameRate(60);
    ofSetVerticalSync(true);
    ofEnableSmoothing();
    //ofEnableAlphaBlending();
    //ofEnableNormalizedTexCoords();
    //ofHideCursor();
    
    glNewList(1, GL_COMPILE);
    glutSolidCube(3);//glutSolidSphere(1.5,8,8);
    glEndList();
    
    boidNum = 200;
    oldVectors.resize( boidNum );//MY CODE

    target = ofVec3f(0, 0, 0);
    
    for (int i = 0; i < boidNum; i++)
    {
        SteeredVehicle v(ofRandom(100)-50, ofRandom(100)-50, ofRandom(100)-50);
        v.maxForce = 0.5f;
        //v.inSightDist = 1000.0f;
        boids.push_back(v);
    }
    
    cam.setDistance(300);
    
    GLfloat color[] = { 0.2, 1.0, 3.2 };
    
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
    glLightfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, color);
    
}

//--------------------------------------------------------------
void testApp::update(){
    
    //fishheadmodel.setRotation(1, 270 + ofGetElapsedTimef() * 60, 0, 0, 1);
    
    openNIDevice.update();
    // pull kinect data do something

    depthiterate = 4;
    //pixelcount
    
    ofVec3f fleefrom;
    bool runaway = FALSE;
    
    std::vector<ofPoint>    NearPoints;
    
    NearPoints.resize( boidNum );
    
    
    
    float       NearDistance[ boidNum ];
    
    for (int i = 0; i < boidNum; i++)
    {
        NearDistance[ i ] = 1000000.0f;
    }
    
    unsigned short   *PTR = &openNIDevice.getDepthRawPixels()[ 0 ];

    for( int y = 0 ; y < 480 ; y += depthiterate )
    {
        for( int x = 0 ; x < 640 ; x += depthiterate )
        {
            unsigned short  Depth = PTR[ ( y * 640 ) + x ];
            
            if( Depth > 0 && Depth < 3000 )
            {
                ofPoint     ProjectivePoint( x, y, Depth );
                
                ofPoint     WorldPoint = openNIDevice.projectiveToWorld( ProjectivePoint );
                fleefrom = ofVec3f(WorldPoint);
                for (int i = 0; i < boidNum; i++)
                {
                    
                    float   DistanceToBoid = boids[ i ].position.distance( WorldPoint );
                    
                    if( DistanceToBoid < NearDistance[ i ] )
                    {
                        NearPoints[ i ] = WorldPoint;
                        if(fleefrom.z > NearPoints[i].z)
                        {fleefrom.z = NearPoints[i].z;}
                        NearDistance[ i ] = DistanceToBoid;
                    
                    }
                }
            }
        }
    }
    
    if( NearDistance[ 0 ] < 1000000.0f )       // changed 1000000.0f this is just to check input
    {
        
        
        for (int i = 0; i < boidNum; i++)
        {
            if( NearDistance[ i ] < 1000.0f )
            {
                runaway = TRUE;
                //boids[ i ].flee( NearPoints[ i ] );
                //boids[ i ].flee(target);
                
                //attempt to change near points to the point with lowest z index 18062013
            }
            else{runaway = FALSE;}
        }
    }


    //boids below
    for (int i = 0; i < boidNum; i++)
    {
        
         
        //boids[i].flock(boids);
        if(runaway == TRUE)
        {boids[i].flee(fleefrom);}
        else{
            boids[i].flock(boids);
            boids[i].seek(target);}
        
        boids[i].wander();
        boids[i].update();
        // add a seek center point 
        boids[i].wrap(900, 900, 1600);
    }
    runaway=FALSE;
    
}

//--------------------------------------------------------------
void testApp::draw(){
    
  //  fishheadmodel.draw();

//boids code below
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glEnable(GL_DEPTH_TEST);

    

    
    cam.begin();
    
    
    
    
    for (int i = 0; i < boidNum; i++)
    {
        glPushMatrix();
        glTranslatef(boids[i].position.x, boids[i].position.y, boids[i].position.z);
        
        GLfloat color[] = { 1.0, 1.0, 1.0, 1.0 };
        
        glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, color);
        glCallList(1);
        glPopMatrix();
        oldVectors[i]=ofVec3f(boids[i].position.x, boids[i].position.y, boids[i].position.z);//can use old vec plus new vec to get orientation :)
                     
    }
    /* debug draw kinect
    unsigned short   *PTR = &openNIDevice.getDepthRawPixels()[ 0 ];
    
    const int   depthiterate = 5;
    
    glColor4f( 0.0f, 0.0f, 1.0f, 1.0f );
    
    glBegin( GL_POINTS );

    for( int y = 0 ; y < 480 ; y += depthiterate )
    {
        for( int x = 0 ; x < 640 ; x += depthiterate )
        {
            unsigned short  Depth = PTR[ ( y * 640 ) + x ];
            
            if( Depth > 0 && Depth < 3000 )
            {
                ofPoint     ProjectivePoint( x, y, Depth );
                
                ofPoint     WorldPoint = openNIDevice.projectiveToWorld( ProjectivePoint );
                
                glVertex3f( WorldPoint.x, WorldPoint.y, WorldPoint.z );
            }
        }
    }
    */
    

    glEnd();
    
    cam.end();

}

//--------------------------------------------------------------
void testApp::exit(){
   openNIDevice.stop();
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



