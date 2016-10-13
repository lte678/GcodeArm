#ifndef H_GCODE
#define H_GCODE
#pragma once

#include "Arduino.h"
#include "HardwareSerial.h"

#define MIN_STEP_TIME 1000
#define MAX_COMMAND_LENGTH 64

class GCode {
public:
	
	static boolean execute(char* command);
private:
	static void line(float newX, float newY, float newZ, float newE);
	static long posX;
	static long posY;
	static long posZ;
	static long posE;
	static long actualX;
	static long actualY;
	static long actualZ;
	static long actualE;
	static float feedrate;
};

#endif