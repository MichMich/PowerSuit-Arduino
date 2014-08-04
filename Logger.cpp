/*
  Logger.cpp - A library for ...
  Created by Michael Teeuw, August 4th, 2014.
  Released under the Apache License 2.0.
*/

#include "Arduino.h"
#include "Logger.h"

Logger::Logger()
{
	Serial.begin(9600);
	Serial.println("Logger ready!");
}

void Logger::log(String string)
{
	Serial.print(millis() / 1000.0f);
	Serial.println(": " + string);
}