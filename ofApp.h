//
// Copyright (c) 2017 Christopher Baker <https://christopherbaker.net>
//
// SPDX-License-Identifier:    MIT
//

#pragma once


#include "ofMain.h"
#include "ofxOscSerial.h"
#include "ofxGui.h"
#include "ofxControlPanel.h"
#include "ofxOsc.h"




class ofApp: public ofBaseApp
{
public:
    void setup() override;
	void update();
    void draw() override;

	void onGuiLoad(bool& ab);
	void onGuiSave(bool& ab);
	
	

    void keyPressed(int key) override;


	///OSC stuff///
    void onOscMessage(const ofxOscMessage& message);
    void onSerialError(const ofxIO::SerialBufferErrorEventArgs& error);

    bool ledState = false;
	

	// TOWARDS SOFTWARES OR OTHER COMPUTERS

	ofxOscSender outOfPalito; // will need ip and port, all at live
	//ofxOscSender destiny2; for later various sendings

	

	// FROM SOFTWARES OR OTHER COMPUTERS TO PALITO

	//ofxOscReceiver goingToPalito; // will need  port, all at live

    ofxIO::OSCSerialDevice device;
	ofParameter <bool> dev_presence;
	int cone;
	///GUI///

	///graph
	ofImage palitoName;
	ofImage background;
	ofTrueTypeFont font;
	ofColor palit_green = ofColor(169, 245, 10, 225);
	guiColor bk_trans;

	///////////////////GUI con la libreria alterna, para los textDropdown

	ofxControlPanel gui; // 
	vector <string> velocities;
	ofParameter <int> bauds; // menus

	vector <string> f_devices;
	ofParameter <int> pOrts;

	//guiTypeTextInput();
	//ofParameter<string> Fill_me = "tomara";
	///////////////////
	
	//ofParameter<string> IP_address;

	/////////////////////////////////////
	////GUI OF default library stuff /////
	//////////////////////////////////////
	ofParameter<string> Incoming_P = "iNCoMinG poRt  (goes pAl-e)";
	ofxLabel Incoming_Port;
	ofxIntField Incoming_Port_IN;

	ofParameter<string> Outgoing_P = "oUtComiNG poRt (gets pAl-e)";
	ofxLabel Outgoing_Port;
	ofxIntField Outgoing_Port_IN;

	ofParameter<string> IP_name = "iP_aDdrEsS";
	ofxLabel IP_address;
	ofxTextField IP_addr;

	ofParameter <bool> start; // begin sending/receiving
	int oneStart = 0; // only kill the osc's doers if have been created

	ofxPanel gui_S;

	
};
