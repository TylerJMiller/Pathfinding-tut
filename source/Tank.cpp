#include "Tank.h"

void Tank::init(int ax, int ay, unsigned int asprite)
{
	gridX = ax;
	gridY = ay;
	sprite = asprite;
}

int Tank::nodeNum()
{
	return gridX + (gridY * graphH);
}

void Tank::Draw()
{
	MoveSprite(sprite, (gridX * tileSize) + graphX + (tileSize/4), (gridY * tileSize) + graphY - (tileSize/4));
	DrawSprite(sprite);
}