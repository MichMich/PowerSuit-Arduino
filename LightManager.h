/*
  LigtManager.h - A library for ...
  Created by Michael Teeuw, August 4th, 2014.
  Released under the Apache License 2.0.
*/

#ifndef LightManager_h
#define LightManager_h

#include "Arduino.h"
#include <Adafruit_NeoPixel.h>

enum EffectMode {
	Loop,
	Sparkle
};

class LightManager
{
  public:
    LightManager();
    void init();
    void update();
    void setSpeed(int speed);
    void setEffectMode(EffectMode effectMode);

  private:
    int _pixel;
    int _speed;
    EffectMode _effectMode;
    void nextPixel();
    
    void effectLoop();
    void effectSparkle();

};

#endif


