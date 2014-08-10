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
  None,
	Loop,
	Sparkle,
  Plasma,
  VU
};

enum LightIdentifier {
  Heart,
  LeftEye,
  RightEye,
  LeftArm,
  RightArm
};

struct Point {
  float x;
  float y;
};

class LightManager
{
  public:
    LightManager();
    void update();
    void setSpeed(byte speed);
    void setEffectMode(EffectMode effectMode);
    void setColorEffect(float red, float green, float blue);

  private:
    byte _frame;
    byte _speed;
    EffectMode _effectMode;
    Adafruit_NeoPixel _neoPixels; 
    elapsedMillis _timeElapsed;

    float _colorEffectRed;
    float _colorEffectGreen;
    float _colorEffectBlue;

    float _phase;
    
    void clearAll();
    void nextPixel();
    void effectLoop(const byte pixelArray[], byte size);
    void effectSparkle();
    void effectPlasma();
    void effectVU(const byte pixelArray[], byte size);

    uint32_t getColorWithBrightness(byte brightness);
    uint32_t getColorWithRGB(byte r, byte g, byte b);

};

#endif


