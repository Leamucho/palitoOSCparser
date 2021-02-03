// 2020 Development by Leandro Muñoz
// Copyright (c) 2017 Christopher Baker <https://christopherbaker.net>
//
// SPDX-License-Identifier:    MIT
//


#include "ofApp.h"


void ofApp::setup()
{
    ofSetLogLevel(OF_LOG_VERBOSE);

	//graphical stuff not GUI


	/////////////
	//GUI alterna
	////////////
	gui.setup("palitoOSCparser", 0, 0);
	gui.setBackgroundColor(255, 255, 255, 0);

	//gui.gBgColor(0, 0, 0, 0);
	//gui.setup.bgColor(255, 255, 255, 0);
	//gui.setup->bgColor(255, 255, 255, 0);
	gui.addPanel("OSCpArsER_hELp", 2, false);
	background.load("background1t.png");
	palitoName.load("pAlitOSCparser.png");

	//gui.setWhichPanel(1); //todo lo que se ve de una; 1 seria la ayuda
	//gui.setWhichColumn(0);
	//gui.addDrawableRect("back", &background, 550, 280);
	
	gui.setWhichPanel(0);

	///Col 0
	gui.setWhichColumn(0);
	gui.guiObjects[0]->setPosition(50, 80);
	///////////
	//BAUDS
	/////////
	velocities.push_back("9600");
	velocities.push_back("19200");
	velocities.push_back("38400");
	velocities.push_back("57600");
	velocities.push_back("74880");
	velocities.push_back("115200");
	velocities.push_back("230400");
	velocities.push_back("250000");
	velocities.push_back("460800");
	velocities.push_back("500000");
	velocities.push_back("1000000");
	velocities.push_back("2000000");

	gui.addTextDropDown(bauds.set("bAuDS veLoCiTIeS", 5), velocities);
	
	
	gui.guiObjects[2]->setBackgroundSelectColor(0, 173, 238, 100);
	gui.guiObjects[2]->setBackgroundColor(0, 173, 238, 100);
	//gui.guiObjects[2]->setTextColor(0, 173, 238, 100);
	//////////	
	//PORTs///
	///////////
	gui.addTextDropDown(pOrts.set("communICaTiOn pOrTs", 0), f_devices);
	
	gui.guiObjects[3]->setBackgroundSelectColor(0, 173, 238, 100);
	gui.guiObjects[3]->setBackgroundColor(0, 173, 238, 100);
	//gui.guiObjects[3]->setTextColor(0, 173, 238, 100);

	//gui.addTextInput(Fill_me.set("right"));

	//////////////
	//START BUTTON
	//////////////
	gui.setWhichColumn(1);

	gui.add(start.set("sTaRRrrT", false));
	gui.guiObjects[4]->setPosition(350, 130);
	

	
	////////////////////////
	///Col 1 other gui//////////
	//////////////////

	//gui.setWhichColumn(1);

	///////////////////////////
	//OF GUI default /////////////////
	/////////////////////////////

	ofEnableBlendMode(OF_BLENDMODE_ALPHA);
	gui_S.setup("uDP");
	gui_S.setPosition(350, 55);
	gui_S.setSize(250, 50);
	gui_S.setHeaderBackgroundColor(ofColor(0, 0));
	gui_S.setBorderColor(ofColor(0, 0));
	gui_S.setTextColor (ofColor(255, 0, 0, 120));
	//colores

	///Ip address
	gui_S.add(IP_address.setup(IP_name, 250,20)); //El label + paramet
	IP_address.setBackgroundColor(ofColor(0, 0, 0, 0));
	gui_S.add(IP_addr.setup("", "192.168.137.1")); //El input text
	IP_addr.setBackgroundColor(ofColor(234, 47, 70, 100));
	IP_addr.setSize(250, 20);

	///incoming port
	gui_S.add(Incoming_Port.setup(Incoming_P, 250, 20)); //El label + paramet
	Incoming_Port.setBackgroundColor(ofColor(0, 0, 0, 0));
	gui_S.add(Incoming_Port_IN.setup("", 9000)); //El input text
	Incoming_Port_IN.setBackgroundColor(ofColor(234, 47, 70, 100));
	Incoming_Port_IN.setSize(250, 20);
	
	///outgoing port
	gui_S.add(Outgoing_Port.setup(Outgoing_P, 250, 20)); //El label + paramet
	Outgoing_Port.setBackgroundColor(ofColor(0, 0, 0, 0));
	gui_S.add(Outgoing_Port_IN.setup("", 10000)); //El input text
	Outgoing_Port_IN.setBackgroundColor(ofColor(234, 47, 70, 100));
	Outgoing_Port_IN.setSize(250, 20);
	
	///
	
	gui.guiObjects[1]->setPosition(50, 140);

	//sin color para el fondo salga
	gui.guiObjects[0]->setBackgroundColor(0, 0, 0, 0);
	gui.guiObjects[1]->setBackgroundColor(0, 0, 0, 0);
	gui.guiObjects[0]->setBackgroundSelectColor(0, 0, 0, 0);
	gui.guiObjects[1]->setBackgroundSelectColor(0, 0, 0, 0);
	ofDisableBlendMode();
	
}

void ofApp::update() {
	gui.update();
	
	//bauds.
	int inPort = Incoming_Port_IN;
	int outPort = Outgoing_Port_IN;
	string ipAd = IP_addr;

	//dev_presence = devicesInfo.empty(); // guardar la boolean de presencia de ardu
	//f_devices.push_back(ofToString(devicesInfo[0]));// no da problemas pero no lo logra...
	
	


	if (start.get() == true) {
		
		ledState = true;
		
		gui.guiObjects[2]->update();

		if ((oneStart == 0)) {

			auto devicesInfo = ofxIO::SerialDeviceUtils::listDevices(); //:: son anti jerarquia... no, si es como . pero entonces? // tambien se usan...
			ofLogNotice("ofApp::setup") << "Connected Devices: "; // esto a la consola grafica de OF

			for (auto& device : devicesInfo) ofLogNotice("ofApp::setup") << "\t" << device; //decir todas las informaciones

			f_devices.push_back(ofToString(devicesInfo[0]));

			if (devicesInfo.empty() == true) {
				f_devices.push_back("none");
			}
			//ofLogNotice("bauds ??") << "bauds are " << gui.guiObjects[0]->displayText;
			//ofLogNotice("bauds ??") << "bauds are " << (gui.guiObjects[2]->getSelectedStringValue());
			//ofLogNotice("bauds ??") << "bauds are " << bauds.getNumListeners();
			if (!devicesInfo.empty())
			{
				//device.setup(devicesInfo[0], 115200);
				// Connect to the first matching device.
				bool success = device.setup(devicesInfo[0], ofToInt((gui.guiObjects[2]->getSelectedStringValue()))); // setup es cómo hacer la conexion, y si da true, success continua, //mirar si hay limit en device
																	//hay que poner setup condicionado de un boton y segun una var en donde 460800
				//bool success = device.setup(devicesInfo[0], 115200);

				if (success) // a
				{
					device.registerAllEvents(this); //aqui es que se conecta!!!!!!
					ofLogNotice("ofApp::setup") << "Successfully setup " << devicesInfo[0];
				}
				else ofLogNotice("ofApp::setup") << "Unable to setup " << devicesInfo[0];
			}
			else ofLogNotice("ofApp::setup") << "No devices connected."; //esto no con log, que salga escrito, un espacio de consola debajo
			oneStart = 1;
		}
		
		
		//device conex stuff
		outOfPalito.setup(ipAd, outPort);
		//goingToPalito.setup(inPort);

		//outOfPalito.start
		//goingToPalito.start;
		// OSC receiver queues up new messages, so you need to iterate
		// through waiting messages to get each incoming message

		// check for waiting messages
		/*while (goingToPalito.hasWaitingMessages()) {
			// get the next message
			ofxOscMessage m;
			goingToPalito.getNextMessage(m);
			// log received message for easier debugging of participants' messages:
			//ofLogVerbose() << "Server received msg " + getOscMsgAsString(m) + " from " + m.getRemoteHost();
			// send to palito 
			device.send(m);
		}*/
		// then clean
		//device.clear;
		
		/// y en el void de serialdevice msg usar ledstate para enviar afuera poroutofpalito
		



	}
	else if (oneStart == 1) {
		//outOfPalito.~ofxOscSender;
		//goingToPalito.stop;
		ledState = false;
		
	}
}

void ofApp::draw()
{
	
	ofBackground(0, 0, 0);
	

	//palitoName.draw(10, 10);
	if (ledState) {
		ofEnableBlendMode(OF_BLENDMODE_ADD);
		ofSetColor(palit_green);    // red, 50% transparent
		ofDrawRectangle(0,0, 662, 301);
		//ofBackground(palit_green);
	}
	else {
		ofEnableBlendMode(OF_BLENDMODE_ALPHA);
		ofSetColor(0, 0, 0);    // red, 50% transparent
		ofDrawRectangle(0, 0, 662, 301);
		//ofBackground(0,0,0,10);
	}
    //ofDrawBitmapStringHighlight("Press a key to toggle the LED.", 20, 40);
	ofSetColor(200, 0, 0, 127);    // red, 50% transparent
	ofDrawRectangle(100, 100, 55, 280);


	ofSetColor(255, 255, 255, 255); //restart color, funciona como tint para images en processing
	background.draw(0, 0);
	palitoName.draw(10, 10);
	gui.draw();
	gui_S.draw();
	ofDisableBlendMode();

}


void ofApp::keyPressed(int key)
{
    ledState = !ledState;

    ofxOscMessage m;
    m.setAddress("/led");
    m.addInt32Arg(ledState);

    device.send(m);
}


void ofApp::onOscMessage(const ofxOscMessage& message)
{
	if (ledState) {
		outOfPalito.sendMessage(message);
		//outOfPalito.;
	}
	
	//aqui enviar por el ip-port
	ofLog() << "Got OSC Message: " << message;

}

void ofApp::onSerialError(const ofxIO::SerialBufferErrorEventArgs& error)
{
    ofLogError() << "Got OSC Error: " << error.exception().displayText(); // to put on console**
}

//--------------------------------------------------------------
void ofApp::onGuiLoad(bool& ab) {
	cout << "onGuiLoad : " << ab << " | " << ofGetFrameNum() << endl;
}

//--------------------------------------------------------------
void ofApp::onGuiSave(bool& ab) {
	cout << "onGuiSave : " << ab << " | " << ofGetFrameNum() << endl;
}



//--------------------------------------------------------------
