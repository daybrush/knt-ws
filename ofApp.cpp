#include "ofApp.h"
//--------------------------------------------------------------
void ofApp::setup(){
    serverInit();
    
    
//    ofSetLogLevel(OF_LOG_VERBOSE);
    
    openNIDevice.setup();
    openNIDevice.addImageGenerator();
    openNIDevice.addDepthGenerator();
    openNIDevice.setRegister(true);
    openNIDevice.setMirror(true);
    
    openNIDevice.addUserGenerator();
    openNIDevice.setMaxNumUsers(2);
    openNIDevice.start();
    
    // set properties for all user masks and point clouds
    //openNIDevice.setUseMaskPixelsAllUsers(true); // if you just want pixels, use this set to true
    openNIDevice.setUseMaskTextureAllUsers(true); // this turns on mask pixels internally AND creates mask textures efficiently
    openNIDevice.setUsePointCloudsAllUsers(true);
    openNIDevice.setPointCloudDrawSizeAllUsers(2); // size of each 'point' in the point cloud
    openNIDevice.setPointCloudResolutionAllUsers(2); // resolution of the mesh created for the point cloud eg., this will use every second depth pixel
    
    verdana.loadFont(ofToDataPath("verdana.ttf"), 24);
}

//--------------------------------------------------------------
void ofApp::update(){
    openNIDevice.update();
}

//--------------------------------------------------------------
void ofApp::draw(){
    ofSetColor(255, 255, 255);
    
    ofPushMatrix();
    // draw debug (ie., image, depth, skeleton)
    openNIDevice.drawDebug();
    ofPopMatrix();
    
    ofPushMatrix();
    // use a blend mode so we can see 'through' the mask(s)
    ofEnableBlendMode(OF_BLENDMODE_ALPHA);
    
    // get number of current users
    int numUsers = openNIDevice.getNumTrackedUsers();
    
    string msg = "";
    // iterate through users
    ofxOpenNIJoint head, leftHand, rightHand;
    for (int i = 0; i < numUsers; i++){
        msg += "p" +ofToString(i) + "=";
        // get a reference to this user
        ofxOpenNIUser & user = openNIDevice.getTrackedUser(i);
        user.drawMask();
        
        ofPushMatrix();
        ofTranslate(320, 240, 10);
        user.drawPointCloud();
        
        // you can also access the mesh:
        
        // MESH REFERENCE
        //ofMesh & mesh = user.getPointCloud();
        // do something with the point cloud mesh
        
        ofPopMatrix();
        ofxOpenNIJoint head = user.getJoint(JOINT_HEAD);
        ofxOpenNIJoint neck = user.getJoint(JOINT_NECK);
        ofxOpenNIJoint leftElbow = user.getJoint(JOINT_LEFT_ELBOW);
        ofxOpenNIJoint rightElbow = user.getJoint(JOINT_RIGHT_ELBOW);
        ofxOpenNIJoint leftHand = user.getJoint(JOINT_LEFT_HAND);
        ofxOpenNIJoint rightHand = user.getJoint(JOINT_RIGHT_HAND);
        ofxOpenNIJoint leftKnee = user.getJoint(JOINT_LEFT_KNEE);
        ofxOpenNIJoint rightKnee = user.getJoint(JOINT_RIGHT_KNEE);
        ofxOpenNIJoint spine = user.getJoint(JOINT_TORSO);
        
        ofPoint leftHandPos = leftHand.getProjectivePosition();
        ofPoint rightHandPos = rightHand.getProjectivePosition();
        msg += JointToString("he", head);
        msg += JointToString("ne", neck);
        msg += JointToString("le", leftElbow);
        msg += JointToString("re", rightElbow);
        msg += JointToString("lh", leftHand);
        msg += JointToString("rh", rightHand);
        msg += JointToString("lk", leftKnee);
        msg += JointToString("rk", rightKnee);
        msg += JointToString("sp", spine);
        
        ofPushMatrix();
        ofSetColor(200,0,0);
        ofCircle(leftHandPos.x + 640,leftHandPos.y,30);
        ofSetColor(0, 0, 200);
        ofCircle(rightHandPos.x + 640, rightHandPos.y, 30);
        ofPopMatrix();
        
        
        msg+= "\n";
    }
    
    ofDisableBlendMode();
    ofPopMatrix();
    
    // draw some info regarding frame counts etc
    ofSetColor(0, 255, 0);
    msg += " MILLIS: " + ofToString(ofGetElapsedTimeMillis()) + " FPS: " + ofToString(ofGetFrameRate()) + " Device FPS: " + ofToString(openNIDevice.getFrameRate());
    
    verdana.drawString(msg, 20, openNIDevice.getNumDevices() * 480 - 20);
}
string ofApp::JointToString(string name, ofxOpenNIJoint &joint) {
    ofPoint pos = joint.getProjectivePosition();
    return name + ":" + ofToString(pos.x) +"|"+ ofToString(pos.y) + "|"+ ofToString(pos.z) +",";
}
//--------------------------------------------------------------
void ofApp::userEvent(ofxOpenNIUserEvent & event){
    // show user event messages in the console
    ofLogNotice() << getUserStatusAsString(event.userStatus) << "for user" << event.id << "from device" << event.deviceID;
}

//--------------------------------------------------------------
void ofApp::exit(){
    openNIDevice.stop();
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){

}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){

}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){

}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){ 

}






////  server

void ofApp::serverInit() {
    
    server.serverInit();
    
    
}
