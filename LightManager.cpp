/*
  LightManager.cpp - A library for ...
  Created by Michael Teeuw, August 4th, 2014.
  Released under the Apache License 2.0.
*/

#include "Arduino.h"
#include "LightManager.h"
#include <Adafruit_NeoPixel.h>
#include <elapsedMillis.h>

const int NUM_PIXELS = 72; //24 + 8 + 8 + 16 + 16
const int NEOPIXEL_PIN = 6;

elapsedMillis timeElapsed;
Adafruit_NeoPixel neoPixels = Adafruit_NeoPixel(NUM_PIXELS, NEOPIXEL_PIN, NEO_GRB + NEO_KHZ800); 

LightManager::LightManager()
{

}

void LightManager::init()
{
	_pixel = 0;
	_speed = 10;
	neoPixels.begin();
	neoPixels.setBrightness(64);
}

// Public functions
void LightManager::update()
{

	if (timeElapsed > _speed) {				
		nextPixel();
		timeElapsed = 0; 
	}
}

void LightManager::setSpeed(int speed)
{
	_speed = speed;
}

void LightManager::setEffectMode(EffectMode effectMode)
{
	_effectMode = effectMode;
}

// Private functions
void LightManager::nextPixel()
{
	neoPixels.setPixelColor(_pixel,0,0,0);
	switch (_effectMode) {
		case Sparkle:
			effectSparkle();
		break;

		case Loop:
		default:
			effectLoop();
		break;
		
	}

	neoPixels.show();
}


void LightManager::effectLoop()
{
	_pixel = (_pixel + 1) % NUM_PIXELS;
	neoPixels.setPixelColor(_pixel,255,255,255);
}

void LightManager::effectSparkle()
{
	_pixel = rand() % NUM_PIXELS; 
	neoPixels.setPixelColor(_pixel,255,255,255);
}
