/*
  EqualizerManager.h - A library for ...
  Created by Michael Teeuw, August 4th, 2014.
  Released under the Apache License 2.0.
*/

#ifndef EqualizerManager_h
#define EqualizerManager_h

#include "Arduino.h"
//#include <elapsedMillis.h>



class EqualizerManager
{
  public:
    EqualizerManager();
    void init();
    void update();

    float bandLow;
    float bandMid;
    float bandHigh;

  private:
    void readMSGEQ7();
};

#endif


