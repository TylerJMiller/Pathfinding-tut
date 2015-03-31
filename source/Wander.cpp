#include "Wander.h"

Wander::Wander()
{
}
Wander::Wander(int asprite, float ax, float ay, float aspeed, float mjitter)
{
	mWillWander = true;
	mInitialized = true;
	mWillDraw = true;
	mSpriteID = asprite;
	mJitter = mjitter;
	mX = ax;
	mY = ay;
	mSpeed = aspeed;
	mDir.x = 0;
	mDir.y = 0;
	mTar.x = 0;
	mTar.y = 0;
	srand(time(NULL));
}

Wander::~Wander()
{
}

void Wander::Update()
{
	if (mWillWander)
	{

		float vx = mJitter * (((float)(rand() % 1000 ) - 500)) / 500;
		float vy = mJitter * (((float)(rand() % 1000 ) - 500)) / 500;

		ModVecDir(glm::vec2(vx, vy));
	}

	mX += mSpeed * mDir.x;
	mY += mSpeed * mDir.y;
	if (mX < 0)
		mX += WINDOWWIDTH;
	if (mX > WINDOWWIDTH)
		mX -= WINDOWWIDTH;
	if (mY < 0)
		mY += WINDOWHEIGHT;
	if (mY > WINDOWHEIGHT)
		mY -= WINDOWHEIGHT;
}

void Wander::ToggleWander()
{
	mDir.x = 0;
	mDir.y = 0;
	mWillWander = !mWillWander;
}

void Wander::Draw()
{
	if (mWillDraw)
	{
		MoveSprite(mSpriteID, mX, mY);
		DrawSprite(mSpriteID);
	}
}

void Wander::ModVecDir(glm::vec2 av)
{
	mDir = glm::normalize(av + mDir);
	//mDir = glm::normalize(mDir);
}

glm::vec2 Wander::GetPosVec()
{
	return glm::vec2(mX, mY);
}
