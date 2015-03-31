#ifndef _HUNTER_H
#define _HUNTER_H

#include "Util.h"

//enum HunterLog{ CHASE, FLEE };

class Hunter
{
public:
	Hunter();
	Hunter(int aSprite, float ax, float ay, float aspeed);
	//Hunter(int aSprite, float ax, float ay, float avecx, float avecy, float aspeed);
	~Hunter();

	void Update();
	void Draw();
	void ToggleDraw();
	void SetTarget(glm::vec2 av);

	int mSpriteID;
	float mX, mY, mSpeed;
	//HunterLog 
	bool mInitialized, mWillDraw;
	glm::vec2 mDir;
	glm::vec2 mTar;
};

#endif