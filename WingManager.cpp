/*
  WingManager.cpp - A library for ...
  Created by Michael Teeuw, August 4th, 2014.
  Released under the Apache License 2.0.
*/

#include "Arduino.h"
#include "WingManager.h"
#include <Servo.h>

const int PIN_LEFT = 5;
const int PIN_RIGHT = 4;

const int DOWNL = 140;
const int UPL = 30;

const int DOWNR = 40;
const int UPR = 150;

Servo servoL;  // create servo object to control a servo 
Servo servoR;  // create servo object to control a servo 

WingManager::WingManager()
{

}

void WingManager::setWing(WingIdentifier wing, float angle)
{
	WingManager::enable();

	switch (wing) {
		case LeftWing:
			servoL.write(map(angle*255,0,255,DOWNL, UPL));
		break;
		case RightWing:
			servoR.write(map(angle*255,0,255,DOWNR, UPR));
		break;
		default:
			servoL.write(map(angle*255,0,255,DOWNL, UPL));
			servoR.write(map(angle*255,0,255,DOWNR, UPR));
		break;
	}	
}

void WingManager::disable()
{
	if (servoL.attached()) servoL.detach();
	if (servoR.attached()) servoR.detach();
}

void WingManager::enable()
{
	if (!servoL.attached()) servoL.attach(PIN_LEFT);
	if (!servoR.attached()) servoR.attach(PIN_RIGHT);
}

