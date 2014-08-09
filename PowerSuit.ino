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
#define CS_WING_ENABLE "CS_WING_ENABLE"
#define CS_WING_DISABLE "CS_WING_DISABLE"

#define LED 13

//Logger logger = Logger();


LightManager lightManager = LightManager();
WingManager wingManager = WingManager();
NunchuckManager nunchuckManager = NunchuckManager();
EqualizerManager equalizerManager = EqualizerManager();
BluetoothManager bluetoothManager = BluetoothManager();

void setup() {
	Serial.begin(9600);
        while(!Serial);

	// Setup peripherals
	lightManager.init();
	wingManager.init();
	nunchuckManager.init();
	equalizerManager.init();
	bluetoothManager.init();
	

	//lightManager.setSpeed(10);

	bluetoothManager.setRXCallback(rxCallback);


}

void loop() {
	// Update peripherals
	lightManager.update();
	wingManager.update();
	nunchuckManager.update();
	equalizerManager.update();
	bluetoothManager.update();


	//control lightspeed
	lightManager.setSpeed(20 - (19 * max(equalizerManager.bandLow,max(equalizerManager.bandMid, equalizerManager.bandHigh))));

	// color control
	if (nunchuckManager.zButton && !nunchuckManager.cButton) {
		colorControl();
	} else {
		lightManager.setColorEffect(equalizerManager.bandLow, equalizerManager.bandMid, equalizerManager.bandHigh);
	}

	// effect control
	if (!nunchuckManager.zButton && !nunchuckManager.cButton) {
		effectControl();
	}

	// wing control
	if (!nunchuckManager.zButton && nunchuckManager.cButton) {
		wingControl();
	}
}

void colorControl()
{
	float r = nunchuckManager.center;
	float g = max(nunchuckManager.northEast, nunchuckManager.southWest);
	float b = max(nunchuckManager.northWest, nunchuckManager.southEast);

	lightManager.setColorEffect(r,g,b);
}


bool isLoop = true;

void effectControl()
{
	bool newIsLoop;
	if (nunchuckManager.west > 0.5) {
		lightManager.setEffectMode(Sparkle);
		newIsLoop = false;
	} else {
		lightManager.setEffectMode(Loop);
		newIsLoop = true;
	}

	if (isLoop != newIsLoop) {
		isLoop = newIsLoop;
		if (isLoop) {
			bluetoothManager.sendString("Loop Mode");
		} else {
			bluetoothManager.sendString("Sparkle Mode");		
		}
	}
}


bool wingsEnabled = false;
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
			bluetoothManager.sendString(CS_WING_ENABLE);
		}

	} else {
		wingManager.disable();
		if (wingsEnabled) {
			wingsEnabled = false;
			bluetoothManager.sendString(CS_WING_DISABLE);
		}
	}
}

void rxCallback(uint8_t *buffer, uint8_t len)
{
  	Serial.print(F("Received: "));
  	for(int i=0; i<len; i++) {
   		Serial.print((char)buffer[i]); 
	}
	Serial.println("");
}

