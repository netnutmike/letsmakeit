/*
Copyright 2014 Genius Idea Studio, LLC

This file is part of the iotdata247 library for Arduino

*/

#if defined(ARDUINO) && ARDUINO >= 100
  #include "Arduino.h"
#else
  #include "WProgram.h"
#endif

#include "iotdata247.h"

#include <MemoryFree.h>

/**
 * Constructor (using arguments is deprecated! Use begin() instead)
 */
iotdata247::iotdata247(){}
iotdata247::iotdata247(const IPAddress ip, const uint16_t localPort){
	if (Ethernet.begin())
}

bool iotdata247::begin(mac[]) {
	if (Ethernet.begin(mac) == 0) {
		return false;
	}
	
	return true;
}

void iotdata247::connect(int appID, char accessKey[], char accessKeyPassword[]) {
  
}

bool iotdata247::isConnected()	{
	unsigned long currentTime = millis();
	if (_lastContact>0 && _lastContact+10000 < currentTime)	{	// Timeout of 10 sec.
		_lastContact = 0;
		return true;
	}
	return false;
}



