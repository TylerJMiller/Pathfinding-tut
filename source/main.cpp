#include "AIE.h"
#include <iostream>
#include "KeyStater.h"

using namespace std;

int maxWidth = 500;
int maxHeight = 500;
void Load(), Update(), Draw();
KeyStater Keys;
const int mapWidth = 10;
const int mapHeight = 10;
const int tileSize = 50;
int hitMap[mapHeight][mapWidth];
int bad, good;

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
			}
		}
		CreateSprite("./images/good.png", 49, 49, false, SColour(255, 255, 255, 255));
		CreateSprite("./images/bad.png", 49, 49, false, SColour(255, 255, 255, 255));
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


		Keys.Update();
		Keys.Debug();

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
				DrawString(keyHold, (tileSize * i), maxWidth - (tileSize * a), SColour(255, 200, 100, 255));
			}
		}
		char mousex[10], mousey[10];
		_itoa_s(Keys.curs.x, mousex, 10);
		_itoa_s(Keys.curs.y, mousey, 10);
		DrawString(mousey, 400, 400, SColour(129, 129, 129, 255));
		DrawString(mousex, 350, 350, SColour(129, 129, 129, 255));
		ClearScreen();

	}