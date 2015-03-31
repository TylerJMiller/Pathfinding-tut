#include "Hunter.h"

Hunter::Hunter()
{
	mInitialized = false;
	mWillDraw = false;
}

Hunter::Hunter(int aSprite, float ax, float ay, float aspeed)
{
	mInitialized = true;
	mWillDraw = true;
	mSpriteID = aSprite;
	mX = ax;
	mY = ay;
	mSpeed = aspeed;
	mDir.x = 0;
	mDir.y = 0;
	mTar.x = ax;
	mTar.y = ay;
}

//Hunter::Hunter(int aSprite, float ax, float ay, float aspeed, float avecx, float avecy)
//{
//	mInitialized = true;
//	mWillDraw = true;
//	mSpriteID = aSprite;
//	mX = ax;
//	mY = ay;
//	mSpeed = aspeed;
//	mDir.x = avecx;
//	mDir.y = avecy;
//	mTar.x = ax;
//	mTar.y = ay;
//}

Hunter::~Hunter()
{
	
}

void Hunter::Update()
{
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

void Hunter::Draw()
{
	if (mWillDraw)
	{
		MoveSprite(mSpriteID, mX, mY);
		DrawSprite(mSpriteID);
	}
}

void Hunter::ToggleDraw()
{
	mWillDraw = !mWillDraw;
}

void Hunter::SetTarget(glm::vec2 av)
{
	mTar = av - glm::vec2(mX, mY);
	mDir = glm::normalize(mTar);
}
