/*
Copyright 2013 Genius Idea Studio, LLC

This file is part of the iotdata247 library for Arduino

*/


/**
  Version 1.0.0
**/


#ifndef iotdata247_h
#define iotdata247_h

#if defined(ARDUINO) && ARDUINO >= 100
  #include "Arduino.h"
#else
  #include "WProgram.h"
#endif


#include <EthernetUdp.h>
#include <SPI.h>
#include <EthernetV2_0.h>
#include <avr/pgmspace.h>

class iotdata247
{
  private:
	EthernetClient client;

	IPAddress _iotdataIP;		// IP address of the iotdata247 switcher
	
	char _sessionID[45];
	char _accessKey[45];
	char _accessKeyPassword[45];
	int _appID;


	uint8_t _packetBuffer[96];   			// Buffer for storing segments of the packets from ATEM and creating answer packets.

	boolean _hasInitialized;  			// If true, the initial reception of the ATEM memory has passed and we can begin to respond during the runLoop()
	unsigned long _lastContact;			// Last time (millis) the switcher sent a packet to us.
	unsigned long _isConnectingTime;	// Set to millis() after the connect() function was called - and it will force runLoop() to finish the connection session.
	unsigned long _lastping;			//

	boolean _connected;					// true is iotdata247 not in use

	
	
  public:
	

    iotdata247();
    void connect(int appID, char accessKey[], char accessKeyPassword[]);
	void clearData();
	void setIntVal();
	void setCharVal();
	void sendData();
	int getCurrentInt();
	
  //private:
	//void _packagedata(uint16_t packetLength);
	

  public:

/********************************
 * General Getter/Setter methods
 ********************************/
  	void serialOutput(boolean serialOutput);
	bool isConnected();

};

#endif

