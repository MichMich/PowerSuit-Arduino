/*
  WingManager.h - A library for ...
  Created by Michael Teeuw, August 4th, 2014.
  Released under the Apache License 2.0.
*/

#ifndef WingManager_h
#define WingManager_h

#include "Arduino.h"



enum WingIdentifier {
	LeftWing,
	RightWing,
  BothWings
};

class WingManager
{
  public:
    WingManager();
    void init();
    void update();
    void setWing(WingIdentifier wing, float angle);
    void disable();

  //private:
    void enable();


};

#endif

