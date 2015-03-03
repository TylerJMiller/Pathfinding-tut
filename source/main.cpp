﻿#include "AIE.h"
#include <iostream>
#include "KeyStater.h"

using namespace std;

//MOVE ME TO A CLASS
struct Entity
{
public:
	int x, y, s;
	bool doDraw;
	void Set(int ax, int ay, int as)
	{
		x = ax;
		y = ay;
		s = as;
	}
	Entity()
	{
	}
	~Entity()
	{
	}
};

//COLLISION, PATH, DRAW
void Finder(int** &c, int** &f, int** &d, int x, int y) 
{
	for (int i = 0; i < 10; i++)
	{
		for (int ii = 0; ii < 10; ii++)
		{
			c[i][ii] = 0;
		}
	}

}


int maxWidth = 500;
int maxHeight = 500;
void Load(), Update(), Draw();
KeyStater Keys;
const int mapWidth = 10;
const int mapHeight = 10;
const int tileSize = 50;
int hitMap[mapHeight][mapWidth];
int findMap[mapHeight][mapWidth];
int drawPath[mapHeight][mapWidth];
Entity hunter, target;


int main(int argc, char* argv[])
{
	Load();
	//Game Loop
	do
	{
		Update();
		Draw();
		if (Keys.IsPressed(VK_ESCAPE))
			return 0;
	} while (!FrameworkUpdate());

	Shutdown();

	return 0;

}

	void Load()
	{
		Initialise(maxWidth, maxHeight, false, "PATHING");
		SetBackgroundColour(SColour(0, 0, 0, 255));
		Keys.Initialize();

		for (int i = 0; i < 10; i++)
		{
			for (int ii = 0; ii < 10; ii++)
			{
				hitMap[i][ii] = 0;
				findMap[i][ii] = 0;
				drawPath[i][ii] = 0;
			}
		}

		CreateSprite("./images/good.png", 49, 49, false, SColour(255, 255, 255, 255));
		CreateSprite("./images/bad.png", 49, 49, false, SColour(255, 255, 255, 255));
		CreateSprite("./images/marked.png", 12, 12, false, SColour(255, 255, 255, 255));
		hunter.Set(0, 0, CreateSprite("./images/hunter.png", 24, 24, false, SColour(255, 255, 255, 255)));
		target.Set(9, 9, CreateSprite("./images/target.png", 24, 24, false, SColour(255, 255, 255, 255)));

		findMap[hunter.y][hunter.x] = -1;
		findMap[target.y][target.x] = -2;
	}

	void Update()
	{
		if (Keys.IsPressed(VK_LBUTTON) && (int)(Keys.curs.y / tileSize) < mapWidth && (int)(Keys.curs.x / tileSize) < mapHeight)
		{
			if (hitMap[(int)(Keys.curs.y / tileSize)][(int)(Keys.curs.x / tileSize)] == 1)
				hitMap[(int)(Keys.curs.y / tileSize)][(int)(Keys.curs.x / tileSize)] = 0;
			else if (hitMap[(int)(Keys.curs.y / tileSize)][(int)(Keys.curs.x / tileSize)] == 0)
				hitMap[(int)(Keys.curs.y / tileSize)][(int)(Keys.curs.x / tileSize)] = 1;
		}
		if (Keys.IsPressed(VK_S) && (int)(Keys.curs.y / tileSize) < mapWidth && (int)(Keys.curs.x / tileSize) < mapHeight)
		{
			if (findMap[(int)(Keys.curs.y / tileSize)][(int)(Keys.curs.x / tileSize)] == 0)
			{
				findMap[hunter.y][hunter.x] = 0;
				hunter.x = (int)(Keys.curs.x / tileSize);
				hunter.y = (int)(Keys.curs.y / tileSize);
				findMap[hunter.y][hunter.x] = -1;
			}
		}
		if (Keys.IsPressed(VK_D) && (int)(Keys.curs.y / tileSize) < mapWidth && (int)(Keys.curs.x / tileSize) < mapHeight)
		{
			if (findMap[(int)(Keys.curs.y / tileSize)][(int)(Keys.curs.x / tileSize)] == 0)
			{
				findMap[target.y][target.x] = 0;
				target.x = (int)(Keys.curs.x / tileSize);
				target.y = (int)(Keys.curs.y / tileSize);
				findMap[target.y][target.x] = -2;
			}
		}

		if (Keys.IsPressed(VK_SPACE))
		{
			int** aa;
			aa = new int*[mapHeight];
			for (int i = 0; i < mapHeight; i++)
			{
				aa[i] = new int[mapWidth];
			}

			int** bb;
			bb = new int*[mapHeight];
			for (int i = 0; i < mapHeight; i++)
			{
				bb[i] = new int[mapWidth];
			}

			int** cc;
			cc = new int*[mapHeight];
			for (int i = 0; i < mapHeight; i++)
			{
				cc[i] = new int[mapWidth];
			}

			for (int i = 0; i < 10; i++)
			{
				for (int ii = 0; ii < 10; ii++)
				{
					aa[i][ii] = hitMap[i][ii];
					bb[i][ii] = findMap[i][ii];
					cc[i][ii] = drawPath[i][ii];
				}
			}
			Finder(aa, bb, cc, mapWidth, mapHeight);
			for (int i = 0; i < 10; i++)
			{
				for (int ii = 0; ii < 10; ii++)
				{
					hitMap[i][ii] = aa[i][ii];
					findMap[i][ii] = bb[i][ii];
					drawPath[i][ii] = cc[i][ii];
				}
			}
		}

		Keys.Update();
	}

	void Draw()
	{


		for (int a = 0; a < mapWidth; a++)
		{
			for (int i = 0; i < mapHeight; i++)
			{
				MoveSprite(hitMap[a][i], (tileSize * i), maxWidth - (tileSize * a));
				DrawSprite(hitMap[a][i]);
				char keyHold[3], pathHold[5];
				_itoa_s(hitMap[a][i], keyHold, 10);
				DrawString(keyHold, (tileSize * i), maxWidth - (tileSize * a) + 2, SColour(255, 200, 100, 255));
				_itoa_s(findMap[a][i], keyHold, 10);
				DrawString(keyHold, (tileSize * i) + 24, maxWidth - (tileSize * a), SColour(255, 255, 255, 255));
				_itoa_s(drawPath[a][i], keyHold, 10);
				DrawString(keyHold, (tileSize * i), maxWidth - (tileSize * a) - 22, SColour(200, 200, 255, 255));
			}
		}

		MoveSprite(hunter.s, (tileSize * hunter.x) + 12, maxWidth - (tileSize * hunter.y) - 12);
		DrawSprite(hunter.s);
		MoveSprite(target.s, (tileSize * target.x) + 12, maxWidth - (tileSize * target.y) - 12);
		DrawSprite(target.s);

		char mousex[10], mousey[10];
		_itoa_s(Keys.curs.x, mousex, 10);
		_itoa_s(Keys.curs.y, mousey, 10);
		DrawString(mousey, 400, 400, SColour(129, 129, 129, 255));
		DrawString(mousex, 350, 350, SColour(129, 129, 129, 255));
		Keys.Debug();
		ClearScreen();

	}