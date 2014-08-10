// PowerSuit.ino

#include <Adafruit_NeoPixel.h>
#include <elapsedMillis.h>
#include <Servo.h> 
#include <Wire.h>
#include <ArduinoNunchuk.h>
#include <SPI.h>
#include "Adafruit_BLE_UART.h"

#include "LightManager.h"
#include "WingManager.h"
#include "NunchuckManager.h"
#include "EqualizerManager.h"
#include "BluetoothManager.h"

//communication string
//#define CS_WINGS_ENABLED "WINGS_ENABLED"
#define CS_WINGS_DISABLED "WINGS_DISABLED"
#define CS_WINGS_BOTH_UP "WINGS_BOTH_UP"
//#define CS_WINGS_BOTH_DOWN "WINGS_BOTH_DOWN"


#define CS_EFFECT_MODE_NONE "EFFECT_MODE_NONE"
#define CS_EFFECT_MODE_LOOP "EFFECT_MODE_LOOP"
#define CS_EFFECT_MODE_SPARKLE "EFFECT_MODE_SPARKLE"
#define CS_EFFECT_MODE_PLASMA "EFFECT_MODE_PLASMA"
#define CS_EFFECT_MODE_VU "EFFECT_MODE_VU"

LightManager lightManager = LightManager();
WingManager wingManager = WingManager();
NunchuckManager nunchuckManager = NunchuckManager();
EqualizerManager equalizerManager = EqualizerManager();
BluetoothManager bluetoothManager = BluetoothManager();

Direction lastDirection = Center;
bool wingsEnabled = false;

void setup() {
	// Initialize peripherals
	nunchuckManager.init();
	bluetoothManager.init();

	lightManager.setEffectMode(Loop);
}

void colorControl()
{
	float r = nunchuckManager.center;
	float g = max(nunchuckManager.west, nunchuckManager.northWest);
	float b = max(nunchuckManager.east, nunchuckManager.northEast);

	g = max(nunchuckManager.north, g);
	b = max(nunchuckManager.north, b);

	r = max(r, nunchuckManager.south);
	g = max(g, nunchuckManager.south);
	b = max(b, nunchuckManager.south);

	lightManager.setColorEffect(r,g,b);
}

void effectControl()
{
	if (nunchuckManager.direction == North) {
		lightManager.setEffectMode(Loop);
		bluetoothManager.sendString(CS_EFFECT_MODE_LOOP);
	} else if (nunchuckManager.direction == South) {
		lightManager.setEffectMode(Plasma);
		bluetoothManager.sendString(CS_EFFECT_MODE_PLASMA);
	} else if (nunchuckManager.direction == West) {
		lightManager.setEffectMode(Sparkle);
		bluetoothManager.sendString(CS_EFFECT_MODE_SPARKLE);
	} else if (nunchuckManager.direction == East) {
		lightManager.setEffectMode(VU);
		bluetoothManager.sendString(CS_EFFECT_MODE_VU);
	} 


}

bool wingsUp = false;
void wingControl()
{
	if (nunchuckManager.south < 0.5) {
		float left = max(nunchuckManager.northWest,nunchuckManager.west);
		float right = max(nunchuckManager.northEast,nunchuckManager.east);

		left = max(nunchuckManager.north, left);
		right = max(nunchuckManager.north, right);

		wingManager.setWing(LeftWing, left);
		wingManager.setWing(RightWing, right);

		if (!wingsEnabled) {
			wingsEnabled = true;
			//bluetoothManager.sendString(CS_WINGS_ENABLED);
		} else {
			if (left == 1 && right == 1 && !wingsUp) {
				bluetoothManager.sendString(CS_WINGS_BOTH_UP);
				wingsUp = true;
			} else if (left < 1 || right < 0) {
				wingsUp = false;
			}
		}

	} else {
		wingManager.disable();
		if (wingsEnabled) {
			wingsEnabled = false;
			bluetoothManager.sendString(CS_WINGS_DISABLED);
		}
	}
}

void loop() {
	// Update peripherals
	lightManager.update();
	nunchuckManager.update();
	equalizerManager.update();
	bluetoothManager.update();

	if (lastDirection != nunchuckManager.direction) {
		lastDirection = nunchuckManager.direction;

		// effect control
		if (!nunchuckManager.zButton && !nunchuckManager.cButton) {
			effectControl();
		}
	}

	//turn of lights 
	if (nunchuckManager.zButton && nunchuckManager.cButton && nunchuckManager.direction == South) {
		lightManager.setEffectMode(None);
		bluetoothManager.sendString(CS_EFFECT_MODE_NONE);
	}

	// control Lightspeed via Equalizer
	lightManager.setSpeed(20 - (19 * max(equalizerManager.bandLow,max(equalizerManager.bandMid, equalizerManager.bandHigh))));

	// color control
	if (nunchuckManager.zButton && !nunchuckManager.cButton) {
		// Manual Control
		colorControl();
	} else {
		// Control via Equalizer
		lightManager.setColorEffect(equalizerManager.bandLow, equalizerManager.bandMid, equalizerManager.bandHigh);
	}

	// wing control
	if (!nunchuckManager.zButton && nunchuckManager.cButton) {
		wingControl();
	}
}



