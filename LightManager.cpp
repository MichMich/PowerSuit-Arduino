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
const int rightEyePixelArray[16] = {54,53,52,51,50,49,48,47,46,45,44,43,42,41,40,55};
const int  leftEyePixelArray[16] = {61,62,63,64,65,66,67,68,69,70,71,56,57,58,59,60};

LightManager::LightManager(): _neoPixels(NUM_PIXELS, NEOPIXEL_PIN, NEO_GRB + NEO_KHZ800)
{

}

void LightManager::init()
{
	_frame = 0;
	_speed = 20;
	_neoPixels.begin();
	_neoPixels.setBrightness(255);

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
			LightManager::clearAll();
			effectSparkle(heartPixelArray, countof(heartPixelArray));
			effectSparkle(leftArmPixelArray, countof(leftArmPixelArray));
			effectSparkle(rightArmPixelArray, countof(rightArmPixelArray));
			effectSparkle(leftEyePixelArray, countof(leftEyePixelArray));
			effectSparkle(rightEyePixelArray, countof(rightEyePixelArray));
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
	// int r = max(0, 255 - (255 * _colorEffectBlue) - (255 * _colorEffectGreen));
	// int g = max(0, 255 - (255 * _colorEffectBlue) - (255 * _colorEffectRed));
	// int b = max(0, 255 - (255 * _colorEffectRed) - (255 * _colorEffectGreen));


	int pixelIndex = _frame % size;
	int segments = size / 8;

	//_neoPixels.setPixelColor(pixelArray[pixelIndex],r,g,b);

	for (int i =0; i < segments; i++) {
		pixelIndex = (pixelIndex + size / segments) % size;

		_neoPixels.setPixelColor(pixelArray[(pixelIndex - 3) % size],getColorWithBrightness(8));
		_neoPixels.setPixelColor(pixelArray[(pixelIndex - 2) % size],getColorWithBrightness(32));
		_neoPixels.setPixelColor(pixelArray[(pixelIndex - 1) % size],getColorWithBrightness(128));
		_neoPixels.setPixelColor(pixelArray[pixelIndex],getColorWithBrightness(255));
		_neoPixels.setPixelColor(pixelArray[(pixelIndex + 1) % size],getColorWithBrightness(128));
		_neoPixels.setPixelColor(pixelArray[(pixelIndex + 2) % size],getColorWithBrightness(32));
		_neoPixels.setPixelColor(pixelArray[(pixelIndex + 3) % size],getColorWithBrightness(8));
	}


}

void LightManager::effectSparkle(const int pixelArray[], int size)
{
	_neoPixels.setPixelColor(pixelArray[rand() % size],getColorWithRGB(255,0,0));
	_neoPixels.setPixelColor(pixelArray[rand() % size],getColorWithRGB(0,255,0));
	_neoPixels.setPixelColor(pixelArray[rand() % size],getColorWithRGB(0,0,255));

	_neoPixels.setPixelColor(pixelArray[rand() % size],getColorWithRGB(255,255,0));
	_neoPixels.setPixelColor(pixelArray[rand() % size],getColorWithRGB(255,0,255));
	_neoPixels.setPixelColor(pixelArray[rand() % size],getColorWithRGB(0,255,255));

}

uint32_t LightManager::getColorWithBrightness(int brightness)
{
	return LightManager::getColorWithRGB(brightness, brightness, brightness);
}

uint32_t LightManager::getColorWithRGB(int r, int g, int b)
{

	int red = r * _colorEffectRed;
	int green = g * _colorEffectGreen;
	int blue = b * _colorEffectBlue;

	// r = max(0, r - (_colorEffectBlue + _colorEffectGreen) / 2 * 255);
	// g = max(0, g - (_colorEffectBlue + _colorEffectRed) / 2 * 255);
	// b = max(0, b - (_colorEffectRed + _colorEffectGreen) / 2 * 255);

	// int r = _colorEffectRed * brightness;
	// int g = _colorEffectBlue * brightness;
	// int b = _colorEffectGreen * brightness;

	return _neoPixels.Color(red, green, blue);
}
