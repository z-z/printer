#include <string>
#include "Gcode.h"

int main(void){
	Gcode gcode = Gcode();
	string command = "G1 X0 Y100 F100 E1";
	gcode.run(command);
}