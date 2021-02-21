#ifndef GCODE_H
#define GCODE_H

#include <Arduino.h>
#include <AccelStepper.h>
#include <Regexp.h>
#include <math.h>

/**
 * данный класс получает на вход строку, содержащую команду G-CODE
 * класс парсит команду и исполняет ее
 *
 * управление моторами происходит с помощью библиотеки AccelStepper,
 * поэтому при инициализации надо передать 4 объекта этого типа
 * соответственно для моторов X, Y, Z и экструдера
 */

class Gcode
{
public:
	Gcode(uint8_t aStepperParams[3], uint8_t bStepperParams[3], uint8_t zStepperParams[3], uint8_t exStepperParams[3]);
	void run(String &command);
	void step();
	bool isRunned();
private:
	AccelStepper _aStepper;
	AccelStepper _bStepper;
	AccelStepper _zStepper;
	AccelStepper _exStepper;

	struct Command {
		float x;
		float y;
		float z;
		float speed;
	};

	Command parseCommand(String &command);
};

#endif
