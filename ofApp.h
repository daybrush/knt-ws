#pragma once

#include "ofxOpenNI.h"
#include "ofMain.h"
#include "WServer.h"

#define NUM_MESSAGES 20 // how many past messages we want to keep



class ofApp : public ofBaseApp{

	public:
		void setup();
		void update();
		void draw();
        void exit();

		void keyPressed(int key);
		void keyReleased(int key);
		void mouseMoved(int x, int y );
		void mouseDragged(int x, int y, int button);
		void mousePressed(int x, int y, int button);
		void mouseReleased(int x, int y, int button);
		void windowResized(int w, int h);
		void dragEvent(ofDragInfo dragInfo);
		void gotMessage(ofMessage msg);
        string JointToString(string name, ofxOpenNIJoint &joint);
        void userEvent(ofxOpenNIUserEvent & event);
        void serverInit();
        ofxOpenNI openNIDevice;
    
        ofTrueTypeFont verdana;
    
private:
    WServer server;
};
