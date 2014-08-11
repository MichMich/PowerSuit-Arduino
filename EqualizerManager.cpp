/*
  EqualizerManager.cpp - A library for ...
  Created by Michael Teeuw, August 4th, 2014.
  Released under the Apache License 2.0.
*/

#include "Arduino.h"
#include "EqualizerManager.h"




const int NUM_PIXELS = 72; //24 + 8 + 8 + 16 + 16
const int NEOPIXEL_PIN = 6;
const int FRAME_COUNT = 48;


const int PIN_STROBE = 10;
const int PIN_RESET = 9;
const int PIN_DATA = 0; //analog

const int LEVEL_MIN = 64;
const int LEVEL_MAX = 450;

// Public functions
EqualizerManager::EqualizerManager()
{
	bandLow = 0;
	bandMid = 0;
	bandHigh = 0;

	pinMode(PIN_RESET, OUTPUT); // reset
	pinMode(PIN_STROBE, OUTPUT); // strobe
	digitalWrite(PIN_RESET,LOW); // reset low
	digitalWrite(PIN_STROBE,HIGH); //pin 5 is RESET on the shield
}



void EqualizerManager::update()
{
	EqualizerManager::readMSGEQ7();
}


// Private functions
void EqualizerManager::readMSGEQ7()
{
	int data[7];

	//reset the data
	digitalWrite(PIN_RESET, HIGH);
	digitalWrite(PIN_RESET, LOW);
	
	//loop thru all 7 bands
	for(int band=0; band <7; band++) {
		digitalWrite(PIN_STROBE,LOW); // go to the next band 
		delayMicroseconds(100); //gather some data
		data[band] = constrain(map(analogRead(PIN_DATA),LEVEL_MIN,LEVEL_MAX,0,1024),0,1024);

		digitalWrite(PIN_STROBE,HIGH); // reset the strobe pin
	}

	// bandLow = ((data[0] + data[1] + data[2]) / 3) / 1024.0;
	// bandMid = ((data[2] + data[3] + data[4]) / 3) / 1024.0;
	// bandHigh = ((data[4] + data[5] + data[6]) / 3) / 1024.0;

	bandLow = max(data[0], data[1]) / 1024.0;
	bandMid = data[3] / 1024.0;
	bandHigh = data[4] / 1024.0;
}

