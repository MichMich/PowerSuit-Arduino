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

	NunchuckManager::west = NunchuckManager::cleanValue((nunchuk.analogX + TRIMX - 128) * -1);
	NunchuckManager::east = NunchuckManager::cleanValue((nunchuk.analogX + TRIMX - 128));
	NunchuckManager::north = NunchuckManager::cleanValue((nunchuk.analogY + TRIMY - 128));
	NunchuckManager::south = NunchuckManager::cleanValue((nunchuk.analogY + TRIMY - 128) * -1);

	NunchuckManager::northEast = (NunchuckManager::north * NunchuckManager::east) / 127;
	NunchuckManager::southEast = (NunchuckManager::south * NunchuckManager::east) / 127;
	NunchuckManager::southWest = (NunchuckManager::south * NunchuckManager::west) / 127;
	NunchuckManager::northWest = (NunchuckManager::north * NunchuckManager::west) / 127;

	NunchuckManager::zButton = nunchuk.zButton;
	NunchuckManager::cButton = nunchuk.cButton;

/*
	if (timeElapsed2 > 1000) {	
		Serial.print("N: ");
		Serial.print(NunchuckManager::north, DEC);

		Serial.print("  NE: ");			
		Serial.print(NunchuckManager::northEast, DEC);

		Serial.print("  E: ");			
		Serial.print(NunchuckManager::east, DEC);

		Serial.print("  SE: ");			
		Serial.print(NunchuckManager::southEast, DEC);

		Serial.print("  S: ");			
		Serial.print(NunchuckManager::south, DEC);

		Serial.print("  SW: ");			
		Serial.print(NunchuckManager::southWest, DEC);

		Serial.print("  W: ");			
		Serial.print(NunchuckManager::west, DEC);

		Serial.print("  NW: ");			
		Serial.print(NunchuckManager::northWest, DEC);

		Serial.print("  zB: ");			
		Serial.print(NunchuckManager::zButton, DEC);

		Serial.print("  cB: ");			
		Serial.print(NunchuckManager::cButton, DEC);

		Serial.println(" ");

		timeElapsed2 = 0; 
	}
*/
}

int NunchuckManager::cleanValue(int value)
{
  value = max(0,value);
  value = min(127,value);
  if (value < 14) value = 0;
  if (value > 114) value = 127;
  
  return value;
}

// Private functions

