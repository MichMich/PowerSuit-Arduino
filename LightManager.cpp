/*
  LightManager.cpp - A library for ...
  Created by Michael Teeuw, August 4th, 2014.
  Released under the Apache License 2.0.
*/

#include "Arduino.h"
#include "LightManager.h"
#include <Adafruit_NeoPixel.h>

#define countof( array ) ( sizeof( array )/sizeof( array[0] ) )

const int NUM_PIXELS = 72; //24 + 8 + 8 + 16 + 16
const int NEOPIXEL_PIN = 6;
const int FRAME_COUNT = 48;

const int    heartPixelArray[24] = {0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,22,23};
const int  leftArmPixelArray[8] = {24,25,26,27,28,29,30,31};
const int rightArmPixelArray[8] = {39,38,37,36,35,34,33,32};
const int rightEyePixelArray[16] = {55,54,53,52,51,50,49,48,47,46,45,44,43,42,41,40};
const int  leftEyePixelArray[16] = {56,57,58,59,60,61,62,63,64,65,66,67,68,69,70,71};

LightManager::LightManager(): _neoPixels(NUM_PIXELS, NEOPIXEL_PIN, NEO_GRB + NEO_KHZ800)
{

}

void LightManager::init()
{
	_frame = 0;
	_speed = 25;
	_neoPixels.begin();
	_neoPixels.setBrightness(64);

	_colorEffectRed = 1;
	_colorEffectGreen = 0.5;
	_colorEffectBlue = 0;
}

// Public functions
void LightManager::update()
{

	if (_timeElapsed > _speed) {				
		nextPixel();
		_timeElapsed = 0; 
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

void LightManager::setColorEffect(float red, float green, float blue)
{
	_colorEffectRed = red;
	_colorEffectGreen = green;
	_colorEffectBlue = blue;	
}

// Private functions
void LightManager::clearAll()
{
	for (int i = 0; i < NUM_PIXELS; i++) {
		_neoPixels.setPixelColor(i,0,0,0);
	}
}

void LightManager::nextPixel()
{
	
	switch (_effectMode) {
		case Sparkle:
			effectSparkle(leftEyePixelArray, countof(leftEyePixelArray));
		break;

		case Loop:
		default:
			LightManager::clearAll();
			effectLoop(heartPixelArray, countof(heartPixelArray));
			effectLoop(leftArmPixelArray, countof(leftArmPixelArray));
			effectLoop(rightArmPixelArray, countof(rightArmPixelArray));
			effectLoop(leftEyePixelArray, countof(leftEyePixelArray));
			effectLoop(rightEyePixelArray, countof(rightEyePixelArray));
		break;
		
	}

	_neoPixels.show();
	_frame = (_frame + 1) % FRAME_COUNT;
}


void LightManager::effectLoop(const int pixelArray[], int size)
{
	int r = max(0, 255 - (255 * _colorEffectBlue) - (255 * _colorEffectGreen));
	int g = max(0, 255 - (255 * _colorEffectBlue) - (255 * _colorEffectRed));
	int b = max(0, 255 - (255 * _colorEffectRed) - (255 * _colorEffectGreen));



	int frame = _frame;
	_neoPixels.setPixelColor(pixelArray[frame % size],r,g,b);

	frame = (frame + 24) % FRAME_COUNT;
	_neoPixels.setPixelColor(pixelArray[frame % size],r,g,b);



}

void LightManager::effectSparkle(const int pixelArray[], int size)
{
	_neoPixels.setPixelColor(_frame,0,0,0);
	_frame = rand() % NUM_PIXELS; 
	_neoPixels.setPixelColor(_frame,255,255,255);
}
