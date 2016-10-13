#include "GCode.h"

char nextCommand[MAX_COMMAND_LENGTH];
short charIndex;

void setup()
{
	Serial.begin(115200);
	charIndex = 0;
}

void loop()
{
	if (Serial.available() > 0) {
		char available;
		available = Serial.read();

		if (available == '\n' || available == '\r') {
			nextCommand[charIndex] = '\0';
			if (!GCode::execute(nextCommand)) {
				Serial.println(F("[ERROR] Failed to parse gcode!"));
			}
			nextCommand[0] = '\0';
		} else {
			nextCommand[charIndex] = available;
			charIndex++;
		}
	}
}
