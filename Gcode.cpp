#include "Gcode.h"

Gcode::Gcode(uint8_t aStepperParams[3], uint8_t bStepperParams[3], uint8_t zStepperParams[3], uint8_t exStepperParams[3])
{
	_aStepper  = AccelStepper(aStepperParams[0], aStepperParams[1], aStepperParams[2], aStepperParams[3]);
	_bStepper  = AccelStepper(bStepperParams[0], bStepperParams[1], bStepperParams[2], bStepperParams[3]);
	_zStepper  = AccelStepper(zStepperParams[0], zStepperParams[1], zStepperParams[2], zStepperParams[3]);
	_exStepper = AccelStepper(exStepperParams[0], exStepperParams[1], exStepperParams[2], exStepperParams[3]);
}

void Gcode::run(String &command)
{
	Command cmd = parseCommand(command);

	float da = (cmd.x + cmd.y) * 2.5;
	float db = (cmd.x - cmd.y) * 2.5;

	_aStepper.moveTo(da);
	_bStepper.moveTo(db);

	float distanceMM = sqrt(pow(_aStepper.distanceToGo(), 2) + pow(_bStepper.distanceToGo(), 2));

	if(distanceMM == 0)
		return;

	float time = distanceMM / cmd.speed;

	float accelerationX = abs(_aStepper.distanceToGo() / time);
	float accelerationY = abs(_bStepper.distanceToGo() / time);

	_aStepper.setAcceleration(accelerationX);
	_bStepper.setAcceleration(accelerationY);
}

void Gcode::step()
{
	_bStepper.run();
	_aStepper.run();
}

Gcode::Command Gcode::parseCommand(String &command)
{
	Command cmd;

	int pos;
	String substr;

	pos = command.indexOf("X");

	if(pos >= 0)
	{
		substr = command.substring((pos + 1), (pos + 8));
		cmd.x = atof(substr.c_str());
	}

	pos = command.indexOf("Y");

	if(pos >= 0)
	{
		substr = command.substring((pos + 1), (pos + 8));
		cmd.y = atof(substr.c_str());
	}

	pos = command.indexOf("Z");

	if(pos >= 0)
	{
		substr = command.substring((pos + 1), (pos + 8));
		cmd.z = atof(substr.c_str());
	}

	pos = command.indexOf("F");

	if(pos >= 0)
	{
		substr = command.substring((pos + 1), (pos + 8));
		cmd.speed = atof(substr.c_str());
	}

	return cmd;
}

/*
Gcode::Command Gcode::parseCommand(String &command)
{
	Command cmd;

	MatchState *m = new MatchState;

	m->Target(command.c_str());

	char buf [20];

	if(m->Match("X(-?[%d.]+)") > 0)
		cmd.x = atoi(m->GetCapture(buf, 0));

	if(m->Match("Y(-?[%d.]+)") > 0)
		cmd.y = atoi(m->GetCapture(buf, 0));

	if(m->Match("F(-?[%d.]+)") > 0)
		cmd.speed = atoi(m->GetCapture(buf, 0));

	delete m;
	delete buf;

	return cmd;
}
*/
bool Gcode::isRunned()
{
	return _aStepper.distanceToGo() > 0 || _bStepper.distanceToGo() > 0;
}