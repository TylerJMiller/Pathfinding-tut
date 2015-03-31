#include "Tank.h"

Tank::Tank()
{
}

Tank::Tank(int ax, int ay, unsigned int asprite)
{
	gridX = ax;
	gridY = ay;
	sprite = asprite;

}

Tank::~Tank()
{
}

void Tank::move(int ax, int ay)
{
	gridX = (int)((ax - GRAPHX) / TILESIZE);
	gridY = (int)((ay - GRAPHY + TILESIZE) / TILESIZE);
}
int Tank::nodeNum()
{
	return gridX + (gridY * GRAPHHEIGHT);
}

void Tank::Draw()
{
	MoveSprite(sprite, (gridX * TILESIZE) + GRAPHX + (TILESIZE / 4), (gridY * TILESIZE) + GRAPHY - (TILESIZE / 4));
	DrawSprite(sprite);
}