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

	int west = NunchuckManager::cleanValue((nunchuk.analogX + TRIMX - 128) * -1);
	int east = NunchuckManager::cleanValue((nunchuk.analogX + TRIMX - 128));
	int north = NunchuckManager::cleanValue((nunchuk.analogY + TRIMY - 128));
	int south = NunchuckManager::cleanValue((nunchuk.analogY + TRIMY - 128) * -1);

	int northEast = (north * east) / 127;
	int southEast = (south * east) / 127;
	int southWest = (south * west) / 127;
	int northWest = (north * west) / 127;

	NunchuckManager::west = west / 127.0;
	NunchuckManager::west = east / 127.0;
	NunchuckManager::north = north / 127.0;
	NunchuckManager::south = south / 127.0;

	NunchuckManager::northEast = northEast / 127.0;
	NunchuckManager::southEast = southEast / 127.0;
	NunchuckManager::southWest = southWest / 127.0;
	NunchuckManager::northWest = northWest / 127.0;

	NunchuckManager::zButton = nunchuk.zButton;
	NunchuckManager::cButton = nunchuk.cButton;


	NunchuckManager::max = max(NunchuckManager::west, max(NunchuckManager::east, max(NunchuckManager::north, max(NunchuckManager::south, max(NunchuckManager::northEast, max(NunchuckManager::southEast, max(NunchuckManager::southWest, NunchuckManager::northWest)))))));
	NunchuckManager::center = 1.0 - NunchuckManager::max;


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
  if (value < 8) value = 0;
  if (value > 119) value = 127;
  
  return value;
}

// Private functions

