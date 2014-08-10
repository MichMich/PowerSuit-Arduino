/*
  BluetoothManager.h - A library for ...
  Created by Michael Teeuw, August 4th, 2014.
  Released under the Apache License 2.0.
*/

#ifndef BluetoothManager_h
#define BluetoothManager_h

#include "Arduino.h"
#include <SPI.h>
#include "Adafruit_BLE_UART.h"

extern "C" 
{
  /* Callback prototypes */
  typedef void (*rx_callback) (uint8_t *buffer, uint8_t len);
}



class BluetoothManager
{
  public:
    BluetoothManager();
    void init();
    void update();

    void setRXCallback(rx_callback rxEvent);
    void sendString(const char * string);

  private:
    Adafruit_BLE_UART _uart;

};

#endif


