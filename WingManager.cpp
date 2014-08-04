/*
  WingManager.cpp - A library for ...
  Created by Michael Teeuw, August 4th, 2014.
  Released under the Apache License 2.0.
*/

#include "Arduino.h"
#include "WingManager.h"
#include <Servo.h>

const int DOWNL = 155;
const int UPL = 50;

const int DOWNR = 40;
const int UPR = 150;

Servo servoL;  // create servo object to control a servo 
Servo servoR;  // create servo object to control a servo 

WingManager::WingManager()
{

}

void WingManager::init()
{
	servoL.attach(5);  
	servoR.attach(4);  

	servoL.write(DOWNL);
	servoR.write(DOWNR);
}

void WingManager::update()
{


}

void WingManager::setWing(WingIdentifier wing, int angle)
{
	switch (wing) {
		case LeftWing:
			servoL.write(angle);
		break;
		case RightWing:
			servoR.write(angle);
		break;
		default:
			servoL.write(angle);
			servoR.write(angle);
		break;
	}	
}

// Private functions

