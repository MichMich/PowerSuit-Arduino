/*
  NunchuckManager.cpp - A library for ...
  Created by Michael Teeuw, August 4th, 2014.
  Released under the Apache License 2.0.
*/

#include "Arduino.h"
#include "NunchuckManager.h"
#include <Wire.h>
#include <ArduinoNunchuk.h>
#include <elapsedMillis.h>


elapsedMillis timeElapsed2;

ArduinoNunchuk nunchuk = ArduinoNunchuk();

const int TRIMX = 0;
const int TRIMY = 0;

NunchuckManager::NunchuckManager()
{

}

void NunchuckManager::init()
{
	nunchuk.init();
}

void NunchuckManager::update()
{
	nunchuk.update();

	NunchuckManager::west = max(0,(nunchuk.analogX + TRIMX - 128) * -1);
	NunchuckManager::east = max(0,(nunchuk.analogX + TRIMX - 128));
	NunchuckManager::north = max(0,(nunchuk.analogY + TRIMY - 128));
	NunchuckManager::south = max(0,(nunchuk.analogY + TRIMY - 128) * -1);

	if (timeElapsed2 > 250) {	
		Serial.print("N: ");
		Serial.print(NunchuckManager::north, DEC);

		Serial.print("  E: ");			
		Serial.print(NunchuckManager::east, DEC);

		Serial.print("  S: ");			
		Serial.print(NunchuckManager::south, DEC);

		Serial.print("  W: ");			
		Serial.print(NunchuckManager::west, DEC);

		Serial.println(" ");

		timeElapsed2 = 0; 
	}
	

}


// Private functions

