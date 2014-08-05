/*
  LigtManager.h - A library for ...
  Created by Michael Teeuw, August 4th, 2014.
  Released under the Apache License 2.0.
*/

#ifndef LightManager_h
#define LightManager_h

#include "Arduino.h"
#include <Adafruit_NeoPixel.h>
#include <elapsedMillis.h>

enum EffectMode {
	Loop,
	Sparkle
};

enum LightIdentifier {
  Heart,
  LeftEye,
  RightEye,
  LeftArm,
  RightArm
};

class LightManager
{
  public:
    LightManager();
    void init();
    void update();
    void setSpeed(int speed);
    void setEffectMode(EffectMode effectMode);
    void setColorEffect(float red, float green, float blue);

  private:
    int _frame;
    int _speed;
    EffectMode _effectMode;
    Adafruit_NeoPixel _neoPixels; 
    elapsedMillis _timeElapsed;

    float _colorEffectRed;
    float _colorEffectGreen;
    float _colorEffectBlue;

    
    void clearAll();
    void nextPixel();
    void effectLoop(const int pixelArray[], int size);
    void effectSparkle(const int pixelArray[], int size);

};

#endif


