#ifndef GCODE_H
#define GCODE_H

#include <iostream>
#include <string>
#include <math.h>
#include "Regexp.h"

using namespace std;

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
	Gcode();
	void run(string command);
	void print(string title, string value);
	void print(string title, int value);
	void print(string title, float value);
// 	void step();
private:
	// куда будем двигаться
	float _targetX;
	float _targetY;

	// с какой скоростью будем двигаться
	float _speed;

	void parseCommand(string command);
};

#endif
