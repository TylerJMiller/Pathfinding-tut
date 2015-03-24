#ifndef _TANK_H
#define _TANK_H

#include "Util.h"

class Tank
{
public:
	void init(int ax, int ay, unsigned int asprite);
	void move(int ax, int ay);
	Tank(){};
	~Tank(){};
	unsigned int gridX, gridY, sprite;
	void Draw();
	int nodeNum();
};

#endif