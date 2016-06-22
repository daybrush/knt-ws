//
//  WServer.hpp
//  myKinectStart
//
//  Created by next on 2016. 6. 21..
//
//

#pragma once

#include <stdio.h>
#include "ofxLibwebsockets.h"
class WServer : public ofBaseApp{
    
public:

//server
ofxLibwebsockets::Server server;
ofTrueTypeFont font;
vector<string> messages;

string  toLoad;
bool    bSendImage;
ofImage currentImage;

    
    void serverInit();
    
// websocket methods
void onConnect( ofxLibwebsockets::Event& args );
void onOpen( ofxLibwebsockets::Event& args );
void onClose( ofxLibwebsockets::Event& args );
void onIdle( ofxLibwebsockets::Event& args );
void onMessage( ofxLibwebsockets::Event& args );
void onBroadcast( ofxLibwebsockets::Event& args );
    void sendMessage(string t);
void update();
    

};