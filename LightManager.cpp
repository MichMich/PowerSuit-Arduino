/*
  LightManager.cpp - A library for ...
  Created by Michael Teeuw, August 4th, 2014.
  Released under the Apache License 2.0.
*/

#include "Arduino.h"
#include "LightManager.h"
#include <Adafruit_NeoPixel.h>

#define countof( array ) ( sizeof( array )/sizeof( array[0] ) )

const byte NUM_PIXELS = 72; //24 + 8 + 8 + 16 + 16
const byte NEOPIXEL_PIN = 6;
const byte FRAME_COUNT = 48;

const byte ROWS = 9;
const byte COLS = 8;

const byte    heartPixelArray[24] = {1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,22,23,0};
const byte  leftArmPixelArray[8] = {24,25,26,27,28,29,30,31};
const byte rightArmPixelArray[8] = {39,38,37,36,35,34,33,32};
const byte rightEyePixelArray[16] = {54,53,52,51,50,49,48,47,46,45,44,43,42,41,40,55};
const byte  leftEyePixelArray[16] = {61,62,63,64,65,66,67,68,69,70,71,56,57,58,59,60};

LightManager::LightManager(): _neoPixels(NUM_PIXELS, NEOPIXEL_PIN, NEO_GRB + NEO_KHZ800)
{
	_frame = 0;
	_speed = 20;
	_neoPixels.begin();
	_neoPixels.setBrightness(255);

	_colorEffectRed = 1;
	_colorEffectGreen = 1;
	_colorEffectBlue = 1;

	_phase = 0.0;

	_effectMode = None;

}


// Public functions
void LightManager::update()
{

	if (_timeElapsed > _speed || _effectMode == Plasma) {				
		nextPixel();
		_timeElapsed = 0; 
	}
}

void LightManager::setSpeed(byte speed)
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
	for (byte i = 0; i < NUM_PIXELS; i++) {
		_neoPixels.setPixelColor(i,0,0,0);
	}
}

void LightManager::nextPixel()
{
	
	switch (_effectMode) {
		case Sparkle:
			LightManager::clearAll();
			effectSparkle();
		break;

		case Loop:
		
			LightManager::clearAll();
			effectLoop(heartPixelArray, countof(heartPixelArray));
			effectLoop(leftArmPixelArray, countof(leftArmPixelArray));
			effectLoop(rightArmPixelArray, countof(rightArmPixelArray));
			effectLoop(leftEyePixelArray, countof(leftEyePixelArray));
			effectLoop(rightEyePixelArray, countof(rightEyePixelArray));
		break;

		case Plasma:
			effectPlasma();
		break;

		case VU:
			effectVU(heartPixelArray, countof(heartPixelArray));
			effectVU(leftArmPixelArray, countof(leftArmPixelArray));
			effectVU(rightArmPixelArray, countof(rightArmPixelArray));
			effectVU(leftEyePixelArray, countof(leftEyePixelArray));
			effectVU(rightEyePixelArray, countof(rightEyePixelArray));
		break;

		case None:
		default:
			LightManager::clearAll();
		break;
		
	}

	_neoPixels.show();
	_frame = (_frame + 1) % FRAME_COUNT;
}


void LightManager::effectLoop(const byte pixelArray[], byte size)
{
	// int r = max(0, 255 - (255 * _colorEffectBlue) - (255 * _colorEffectGreen));
	// int g = max(0, 255 - (255 * _colorEffectBlue) - (255 * _colorEffectRed));
	// int b = max(0, 255 - (255 * _colorEffectRed) - (255 * _colorEffectGreen));


	byte pixelIndex = _frame % size;
	byte segments = size / 8;

	//_neoPixels.setPixelColor(pixelArray[pixelIndex],r,g,b);

	for (byte i =0; i < segments; i++) {
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

void LightManager::effectVU(const byte pixelArray[], byte size)
{


	int redPower = 255 * _colorEffectRed * size/2;
	int greenPower = 255 * _colorEffectGreen * size/2;
	int bluePower = 255 * _colorEffectBlue * size/2;

    for (byte pixelIndex = 0; pixelIndex < size/2; pixelIndex++) {


		byte red = constrain(redPower,0,255);
		byte green = constrain(greenPower,0,255);
		byte blue = constrain(bluePower,0,255);



		_neoPixels.setPixelColor(pixelArray[pixelIndex + size/2],red,green,blue);
		_neoPixels.setPixelColor(pixelArray[size/2 - pixelIndex - 1],red,green,blue);

		redPower -= red;
		bluePower -= blue;
		greenPower -= green;
    }
}


void LightManager::effectSparkle()
{
	_neoPixels.setPixelColor(rand() % NUM_PIXELS,getColorWithRGB(255,255,255));
	_neoPixels.setPixelColor(rand() % NUM_PIXELS,getColorWithRGB(255,255,255));
	_neoPixels.setPixelColor(rand() % NUM_PIXELS,getColorWithRGB(255,255,255));
}



void LightManager::effectPlasma()
{
  _phase += 0.08;
  //_phase += (_colorEffectRed / 3) + 0.1;

  // The two points move along Lissajious curves, see: http://en.wikipedia.org/wiki/Lissajous_curve
  // We want values that fit the LED grid: x values between 0..13, y values between 0..8 .
  // The sin() function returns values in the range of -1.0..1.0, so scale these to our desired ranges.
  // The _phase value is multiplied by various constants; I chose these semi-randomly, to produce a nice motion.
  Point p1 = { (sin(_phase*1.000)+1.0) * 4.5, (sin(_phase*1.310)+1.0) * 4.0 };
  Point p2 = { (sin(_phase*1.770)+1.0) * 4.5, (sin(_phase*2.865)+1.0) * 4.0 };
  Point p3 = { (sin(_phase*0.250)+1.0) * 4.5, (sin(_phase*0.750)+1.0) * 4.0 };
  
  byte row, col;
  
  // For each row...
  for( row=0; row<ROWS; row++ ) {
    float row_f = float(row);  // Optimization: Keep a floating point value of the row number, instead of recasting it repeatedly.
    
    // For each column...
    for( col=0; col<COLS; col++ ) {
      float col_f = float(col);  // Optimization.
      
      // Calculate the distance between this LED, and p1.
      Point dist1 = { col_f - p1.x, row_f - p1.y };  // The vector from p1 to this LED.
      float distance1 = sqrt( dist1.x*dist1.x + dist1.y*dist1.y );
      
      // Calculate the distance between this LED, and p2.
      Point dist2 = { col_f - p2.x, row_f - p2.y };  // The vector from p2 to this LED.
      float distance2 = sqrt( dist2.x*dist2.x + dist2.y*dist2.y );
      
      // Calculate the distance between this LED, and p3.
      Point dist3 = { col_f - p3.x, row_f - p3.y };  // The vector from p3 to this LED.
      float distance3 = sqrt( dist3.x*dist3.x + dist3.y*dist3.y );
      
      // Warp the distance with a sin() function. As the distance value increases, the LEDs will get light,dark,light,dark,etc...
      // You can use a cos() for slightly different shading, or experiment with other functions. Go crazy!
      float color_1 = distance1;  // range: 0.0...1.0
      float color_2 = distance2;
      float color_3 = distance3;
      float color_4 = (sin( distance1 * distance2 * 0.11 )) + 2.0 * 0.5;
      
      // Square the color_f value to weight it towards 0. The image will be darker and have higher contrast.
      color_1 *= color_1 * color_4;
      color_2 *= color_2 * color_4;
      color_3 *= color_3 * color_4;
      color_4 *= color_4;
 
      // Scale the color up to 0..7 . Max brightness is 7.
      //strip.setPixelColor(col + (8 * row), strip.Color(color_4, 0, 0) );
      _neoPixels.setPixelColor(col + (COLS * row), getColorWithRGB(color_1, color_2, color_3));
    }
  }

}


uint32_t LightManager::getColorWithBrightness(byte brightness)
{
	return LightManager::getColorWithRGB(brightness, brightness, brightness);
}

uint32_t LightManager::getColorWithRGB(byte r, byte g, byte b)
{
	return _neoPixels.Color(r * _colorEffectRed, g * _colorEffectGreen, b * _colorEffectBlue);
}
