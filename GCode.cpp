#include "Gcode.h"

long GCode::posX = 0l;
long GCode::posY = 0l;
long GCode::posZ = 0l;
long GCode::posE = 0l;
float GCode::feedrate = 10.0f;

boolean GCode::execute(char *command) {
	char blocks[16][16];
	char *tempBlock;

	short comIndex = 0; //Block length (max index)

	tempBlock = strtok(command, " ");

	strcpy(blocks[0], " ");

	while (tempBlock != NULL) {
		strcpy(blocks[comIndex], tempBlock);
		comIndex++;
		tempBlock = strtok(NULL, " ");
	}

	for (int i = 0; i <= comIndex; i++) {
		
	}

	if (strcmp(blocks[0], "G0") == 0 || strcmp(blocks[0], "G1") == 0) {
		float paramX = 0.0f;
		float paramY = 0.0f;
		float paramZ = 0.0f;
		float paramE = 0.0f;

		int paramXdir = 1.0f;
		int paramYdir = 1.0f;
		int paramZdir = 1.0f;
		int paramEdir = 1.0f;
		for (int i = 0; i <= comIndex; i++) {
			if (blocks[i][0] == 'X') {
				blocks[i][0] = '0';
				paramX = atof(blocks[i]);
			}
			else if (blocks[i][0] == 'Y') {
				blocks[i][0] = '0';
				paramY = atof(blocks[i]);
			}
			else if (blocks[i][0] == 'Z') {
				blocks[i][0] = '0';
				paramZ = atof(blocks[i]);
			}
			else if (blocks[i][0] == 'E') {
				blocks[i][0] = '0';
				paramE = atof(blocks[i]);
			}
		}

		line(paramX, paramY, paramZ, paramE);

	}

	return true;
}

void GCode::line(float newX, float newY, float newZ, float newE) {
	long dx = newX - posX;
	long dy = newY - posY;
	long dz = newZ - posZ;
	long de = newE - posE;
	float dt;

	long lastTime = millis();

	short dzd = 1;
	boolean moving = true;

	if (dz < 0) dzd = -1;

	while (moving) {
		dt = float(millis() - lastTime) / 1000.0f;

		posZ += (feedrate / dz) * dt * dzd;

		if (dzd != -1 && posZ < newZ) moving = false;
		if (dzd == -1 && posZ > newZ) moving = false;
	}
}