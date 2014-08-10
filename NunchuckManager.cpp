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




ArduinoNunchuk nunchuk = ArduinoNunchuk();

const int TRIMX = 0;
const int TRIMY = 0;

NunchuckManager::NunchuckManager()
{
	direction = Center;
}

void NunchuckManager::init()
{
	nunchuk.init();
}

void NunchuckManager::update()
{
	nunchuk.update();

	west = cleanValue((nunchuk.analogX + TRIMX - 128) * -1) / 127.0;
	east = cleanValue((nunchuk.analogX + TRIMX - 128)) / 127.0;
	north = cleanValue((nunchuk.analogY + TRIMY - 128)) / 127.0;
	south = cleanValue((nunchuk.analogY + TRIMY - 128) * -1) / 127.0;

	northEast = (north * east);
	southEast = (south * east);
	southWest = (south * west);
	northWest = (north * west);

	zButton = nunchuk.zButton;
	cButton = nunchuk.cButton;

	max = max(west, max(east, max(north, max(south, max(northEast, max(southEast, max(southWest, northWest)))))));
	center = 1.0 - max;

	if (northEast == 1) {
		direction = NorthEast;
	} else if(southEast == 1) {
		direction = SouthEast;
	} else if(southWest == 1) {
		direction = SouthWest;
	} else if(northWest == 1) {
		direction = NorthWest;
	} else if(north == 1) {
		direction = North;
	} else if(east == 1) {
		direction = East;
	} else if(south == 1) {
		direction = South;
	} else if(west == 1) {
		direction = West;
	} else if (center == 1) {
		direction = Center;
	}

	/*
		Serial.print("N: ");
		Serial.print(north, DEC);

		Serial.print("  NE: ");			
		Serial.print(northEast, DEC);

		Serial.print("  E: ");			
		Serial.print(east, DEC);

		Serial.print("  SE: ");			
		Serial.print(southEast, DEC);

		Serial.print("  S: ");			
		Serial.print(south, DEC);

		Serial.print("  SW: ");			
		Serial.print(southWest, DEC);

		Serial.print("  W: ");			
		Serial.print(west, DEC);

		Serial.print("  NW: ");			
		Serial.print(northWest, DEC);

		Serial.print("  zB: ");			
		Serial.print(zButton, DEC);

		Serial.print("  cB: ");			
		Serial.print(cButton, DEC);

		Serial.println(" ");
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

