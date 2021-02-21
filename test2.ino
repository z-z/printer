#include <SoftwareSerial.h>
#include <AccelStepper.h>
#include <Gcode.h>

#define READY_PIN 12

uint8_t aStepperParams[3] = {1, 3, 2};
uint8_t bStepperParams[3] = {1, 5, 4};
uint8_t zStepperParams[3] = {1, 7, 6};
uint8_t exStepperParams[3] = {1, 9, 8};

Gcode gcode(aStepperParams, bStepperParams, zStepperParams, exStepperParams);

SoftwareSerial mainSerial(10, 11); // RX, TX

void setup() {
	Serial.begin(9600);
	while(!Serial){;}
	mainSerial.begin(9600);
	while(!mainSerial){;}

	pinMode(READY_PIN, OUTPUT);
	digitalWrite(READY_PIN, HIGH);
}

void loop()
{
	if(mainSerial.available())
	{
		digitalWrite(READY_PIN, LOW);
		String command = mainSerial.readString();
		gcode.run(command);
	}

	gcode.step();

	if(gcode.isRunned())
		digitalWrite(READY_PIN, LOW);
	else
		digitalWrite(READY_PIN, HIGH);
}


// NANO
