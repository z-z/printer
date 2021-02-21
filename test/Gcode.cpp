#include "Gcode.h"

Gcode::Gcode() {}

void Gcode::run(string command)
{
	print("Комманда", command);
	parseCommand(command);

	print("Расстояние по X в мм", _targetX);
	print("Расстояние по Y в мм", _targetY);

	float distanceMM = sqrt(pow(_targetX, 2) + pow(_targetY, 2));
	print("Расстояние по диагонали в мм", distanceMM);

	float time = distanceMM / _speed;
	print("Скорость прохождения (мм / с)", _speed);
	print("Время прохождения (c)", time);

	float stepsX = _targetX * 2.5 + _targetY * 2.5;
	float stepsY = _targetX * 2.5 - _targetY * 2.5;

	print("Количество шагов мотора X", stepsX);
	print("Количество шагов мотора Y", stepsY);

	float accelerationX = stepsX / time;
	float accelerationY = stepsY / time;

	print("Ускорение мотора X", accelerationX);
	print("Ускорение мотора Y", accelerationY);
}

void Gcode::parseCommand(string command)
{
	MatchState m;

	char* chr = strdup(command.c_str());

	m.Target(chr);

	char buf [10];

	if(m.Match("X(-?[%d.]+)") > 0)
		_targetX = atoi(m.GetCapture(buf, 0));

	if(m.Match("Y(-?[%d.]+)") > 0)
		_targetY = atoi(m.GetCapture(buf, 0));

	if(m.Match("F(-?[%d.]+)") > 0)
		_speed = atoi(m.GetCapture(buf, 0));
}

void Gcode::print(string title, int value)
{
	cout << title << ": " << value << endl;
}

void Gcode::print(string title, string value)
{
	cout << title << ": " << value << endl;
}

void Gcode::print(string title, float value)
{
	cout << title << ": " << value << endl;
}