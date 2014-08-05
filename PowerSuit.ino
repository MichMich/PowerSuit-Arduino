// PowerSuit.ino

#include <Logger.h>
#include <Adafruit_NeoPixel.h>
#include <elapsedMillis.h>
#include <Servo.h> 
#include <Wire.h>
#include <ArduinoNunchuk.h>


#include "LightManager.h"
#include "WingManager.h"
#include "NunchuckManager.h"


#define LED 13

//Logger logger = Logger();


LightManager lightManager = LightManager();
WingManager wingManager = WingManager();
NunchuckManager nunchuckManager = NunchuckManager();

void setup() {
	Serial.begin(9600);
        while(!Serial);

	// Setup peripherals
	lightManager.init();
	wingManager.init();
	nunchuckManager.init();
	

	//lightManager.setSpeed(10);
	//lightManager.setEffectMode(Sparkle);



}

void loop() {
	// Update peripherals
	lightManager.update();
	wingManager.update();
	nunchuckManager.update();



	// color control
	if (!nunchuckManager.zButton && !nunchuckManager.cButton) {
		colorControl();
	}

	// effect control
	if (nunchuckManager.zButton && !nunchuckManager.cButton) {
		effectControl();
	}

	// wing control
	if (!nunchuckManager.zButton && nunchuckManager.cButton) {
		wingControl();
	}
}

void colorControl()
{
	lightManager.setColorEffect(nunchuckManager.north / 127.0, nunchuckManager.southEast / 127.0, nunchuckManager.southWest / 127.0);
}

void effectControl()
{

}

void wingControl()
{
	if (nunchuckManager.south < 64) {
		float left = max(nunchuckManager.northWest / 127.0,nunchuckManager.west / 127.0);
		float right = max(nunchuckManager.northEast / 127.0,nunchuckManager.east / 127.0);

		left = max(nunchuckManager.north / 127.0, left);
		right = max(nunchuckManager.north / 127.0, right);

		wingManager.setWing(LeftWing, left);
		wingManager.setWing(RightWing, right);

	} else {
		wingManager.disable();
	}
}

