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
NunchuckManager nunchukManager = NunchuckManager();

void setup() {
	Serial.begin(9600);

	// Setup peripherals
	lightManager.init();
	// wingManager.init();
	nunchukManager.init();
	

	//lightManager.setSpeed(10);
	//lightManager.setEffectMode(Sparkle);

}

void loop() {
	// Update peripherals

	lightManager.update();
	wingManager.update();
	nunchukManager.update();

	//lightManager.setSpeed(nunchuk.analogX);
	//lightManager.setEffectMode((nunchuk.zButton) ? Sparkle : Loop);


}


#define TRIMX 3
#define TRIMY 0

#define DOWNL 155
#define UPL 50

#define DOWNR 40
#define UPR 150

/*
void controlWings()
{
	int inputLeft = (nunchuk.analogX + TRIMX - 128) * -1;
	int inputRight = (nunchuk.analogX + TRIMX - 128);

	int inputUp = (nunchuk.analogY + TRIMY - 128);
	int inputDown = (nunchuk.analogY + TRIMY - 128) * -1;

	inputLeft = trimInt(inputLeft, 0, 125);
	inputRight = trimInt(inputRight, 0, 125);

	inputUp = trimInt(inputUp, 0, 125);
	inputDown = trimInt(inputDown, 0, 125);


	int angleLeft =  map((inputUp > inputLeft)  ? inputUp : inputLeft,  0, 125, DOWNL, UPL);
	int angleRight = map((inputUp > inputRight) ? inputUp : inputRight, 0, 125, DOWNR, UPR);


	wingManager.setWing(LeftWing, angleLeft);
	wingManager.setWing(RightWing, angleRight);
}

int trimInt(int value, int min, int max)
{
	if (value < min) value = min;
	if (value > max) value = max;
	return value;
}
*/

