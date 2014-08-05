/*
  WingManager.h - A library for ...
  Created by Michael Teeuw, August 4th, 2014.
  Released under the Apache License 2.0.
*/

#ifndef NunchuckManager_h
#define NunchuckManager_h

#include "Arduino.h"





class NunchuckManager
{
  public:
    NunchuckManager();
    void init();
    void update();

    int north;
    int northEast;
    int east;
    int southEast;
    int south;
    int southWest;
    int west;
    int northWest;

    bool zButton;
    bool cButton;

  private:
    int cleanValue(int value);



};

#endif

