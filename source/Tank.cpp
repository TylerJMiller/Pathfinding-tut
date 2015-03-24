#include "Tank.h"

void Tank::init(int ax, int ay, unsigned int asprite)
{
	gridX = ax;
	gridY = ay;
	sprite = asprite;
}
void Tank::move(int ax, int ay)
{
	gridX = (int)((ax - graphX) / tileSize);
	gridY = (int)((ay - graphY + tileSize) / tileSize);
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