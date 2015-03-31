#ifndef _WANDER_H
#define _WANDER_H

#include "Hunter.h"

class Wander : private Hunter
{
public:
	Wander();
	Wander(int aSprite, float ax, float ay, float aspeed, float ajitter);
	~Wander();
	void Update();
	void ToggleWander();
	void Draw();
	void ModVecDir(glm::vec2 av);
	glm::vec2 GetPosVec();
private:
	bool mWillWander;
	float mJitter;
};

#endif