/*
  BluetoothManager.cpp - A library for ...
  Created by Michael Teeuw, August 4th, 2014.
  Released under the Apache License 2.0.
*/

#include "Arduino.h"
#include <SPI.h>
#include "Adafruit_BLE_UART.h"
#include "BluetoothManager.h"

const int ADAFRUITBLE_REQ = 7;
const int ADAFRUITBLE_RDY = 2;
const int ADAFRUITBLE_RST = 8;


// Public functions
BluetoothManager::BluetoothManager() : _uart(ADAFRUITBLE_REQ, ADAFRUITBLE_RDY, ADAFRUITBLE_RST)
{

}

void BluetoothManager::init()
{
	_uart.begin();
}

void BluetoothManager::update()
{
	_uart.pollACI();	
}

void BluetoothManager::setRXCallback(rx_callback event)
{
	  _uart.setRXcallback(event);
}

void BluetoothManager::sendString(const char * string)
{
    _uart.print(string);
}




