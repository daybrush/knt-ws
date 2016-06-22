//
//  WServer.cpp
//  myKinectStart
//
//  Created by next on 2016. 6. 21..
//
//

#include "WServer.h"

void WServer::serverInit() {
    
    ofxLibwebsockets::ServerOptions options = ofxLibwebsockets::defaultServerOptions();
    
    options.port = 9093;
    
    bool connected = server.setup( options );
    
    // this adds your app as a listener for the server
    server.addListener(this);
    
    // setup message queue
    
    font.load("myriad.ttf", 20);
    messages.push_back("WebSocket server setup at "+ofToString( server.getPort() ) + ( server.usingSSL() ? " with SSL" : " without SSL") );
    
    ofBackground(0);
    ofSetFrameRate(60);
    bSendImage = false;
    
}



void WServer::onConnect( ofxLibwebsockets::Event& args ){
    cout<<"on connected"<<endl;
}
void WServer::update(){
    cout<< "update" << endl;
}
//--------------------------------------------------------------
void WServer::onOpen( ofxLibwebsockets::Event& args ){
    cout<<"new connection open"<<endl;
    messages.push_back("New connection from " + args.conn.getClientIP() );
    
    // send the latest image if there is one!
    if ( currentImage.bAllocated() ){
        args.conn.send( ofToString(currentImage.getWidth()) +":"+ ofToString( currentImage.getHeight() ) +":"+ ofToString( currentImage.getImageType() ) );
        args.conn.sendBinary( currentImage );
    }
}

//--------------------------------------------------------------
void WServer::onClose( ofxLibwebsockets::Event& args ){
    cout<<"on close"<<endl;
    messages.push_back("Connection closed");
}

//--------------------------------------------------------------
void WServer::onIdle( ofxLibwebsockets::Event& args ){
    cout<<"on idle"<<endl;
}

//--------------------------------------------------------------
void WServer::onMessage( ofxLibwebsockets::Event& args ){
    cout<<"got message "<<args.message<<endl;
    
    // trace out string messages or JSON messages!
    // args.json is null if badly formed or just not JOSN
    if ( !args.json.isNull() ){
        messages.push_back("New message: " + args.json.toStyledString() + " from " + args.conn.getClientName() );
    } else {
        messages.push_back("New message: " + args.message + " from " + args.conn.getClientName() );
    }
    
    //if (messages.size() > NUM_MESSAGES) messages.erase( messages.begin() );
    
    // echo server = send message right back!
    args.conn.send( args.message );
}

//--------------------------------------------------------------
void WServer::onBroadcast( ofxLibwebsockets::Event& args ){
    cout<<"got broadcast "<<args.message<<endl;
}
void WServer::sendMessage(string t) {
    server.send(t);
}



