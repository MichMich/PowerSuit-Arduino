/*
  WingManager.h - A library for ...
  Created by Michael Teeuw, August 4th, 2014.
  Released under the Apache License 2.0.
*/

#ifndef NunchuckManager_h
#define NunchuckManager_h

#include "Arduino.h"



enum Direction {
  Nort,
  North,
  NorthEast,
  East,
  SouthEast,
  South,
  SouthWest,
  West,
  NorthWest,
  Center
};


class NunchuckManager
{
  public:
    NunchuckManager();
    void init();
    void update();

    float north;
    float northEast;
    float east;
    float southEast;
    float south;
    float southWest;
    float west;
    float northWest;

    float max;
    float center;
    
    bool zButton;
    bool cButton;

    Direction direction;

  private:
    int cleanValue(int value);

};

#endif

