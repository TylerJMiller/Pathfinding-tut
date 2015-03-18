#include "AIE.h"
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

int maxWidth = 500;
int maxHeight = 500;
void Load(), Update(), Draw();
KeyStater Keys;
const int mapWidth = 10;
const int mapHeight = 10;
const int tileSize = 50;
int hitMap[mapHeight][mapWidth];
int findMap[mapHeight][mapWidth];
int pathMap[mapHeight][mapWidth];
Entity hunter, target;

//COLLISION, FINDER/POINT, PATH
int Finder(int** &c, int** &f, int** &p) 
{
	for (int n = 1; n != -1; n++)
	{

		int testnum = 0;

		for (int i = 0; i < 10; i++)
		{

			for (int ii = 0; ii < 10; ii++)
			{

				if (p[i][ii] == n && c[i][ii] != 1)
				{
					if (i < 9)
					{
						if (f[i + 1][ii] == -1)
						{
							if (n > 1)
								c[i][ii] = 2;
							return p[i][ii];
						}
						if (p[i + 1][ii] == 0 && c[i + 1][ii] != 1)		//DOWN
						{
							p[i + 1][ii] = n + 1;
							testnum++;
						}
					}
					if (i > 0)
					{
						if (f[i - 1][ii] == -1)
						{
							if (n > 1)
								c[i][ii] = 2;
							return p[i][ii];
						}
						if (p[i - 1][ii] == 0 && c[i - 1][ii] != 1)		//UP
						{
							p[i - 1][ii] = n + 1;
							testnum++;
						}
					}
					if (ii < 9)
					{
						if (f[i][ii + 1] == -1)
						{
							if (n > 1)
								c[i][ii] = 2;
							return p[i][ii];
						}
						if (p[i][ii + 1] == 0 && c[i][ii + 1] != 1)		//RIGHT
						{
							p[i][ii + 1] = n + 1;
							testnum++;
						}
					}
					if (ii > 0)
					{
						if (f[i][ii - 1] == -1)
						{
							if (n > 1)
								c[i][ii] = 2;
							return p[i][ii];
						}
						if (p[i][ii - 1] == 0 && c[i][ii - 1] != 1)		//LEFT
						{
							p[i][ii - 1] = n + 1;
							testnum++;
						}
					}

				}



			}

		}

		if (testnum == 0)
		{
			n = -2;
		}
	}
	return 0;
}

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
				pathMap[i][ii] = 0;
			}
		}

		CreateSprite("./images/good.png", 49, 49, false, SColour(255, 255, 255, 255));
		CreateSprite("./images/bad.png", 49, 49, false, SColour(255, 255, 255, 255));
		CreateSprite("./images/marked.png", 12, 12, false, SColour(255, 255, 255, 255));
		hunter.Set(0, 0, CreateSprite("./images/hunter.png", 24, 24, false, SColour(255, 255, 255, 255)));
		target.Set(9, 9, CreateSprite("./images/target.png", 24, 24, false, SColour(255, 255, 255, 255)));

		findMap[hunter.y][hunter.x] = 1;
		pathMap[hunter.y][hunter.x] = 1;
		findMap[target.y][target.x] = -1;
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
				pathMap[hunter.y][hunter.x] = 0;
				hunter.x = (int)(Keys.curs.x / tileSize);
				hunter.y = (int)(Keys.curs.y / tileSize);
				findMap[hunter.y][hunter.x] = 1;
				pathMap[hunter.y][hunter.x] = 1;
			}
		}
		if (Keys.IsPressed(VK_D) && (int)(Keys.curs.y / tileSize) < mapWidth && (int)(Keys.curs.x / tileSize) < mapHeight)
		{
			if (findMap[(int)(Keys.curs.y / tileSize)][(int)(Keys.curs.x / tileSize)] == 0)
			{
				findMap[target.y][target.x] = 0;
				target.x = (int)(Keys.curs.x / tileSize);
				target.y = (int)(Keys.curs.y / tileSize);
				findMap[target.y][target.x] = -1;
			}
		}
		if (Keys.IsPressed(VK_B))
		{
			for (int i = 0; i < 10; i++)
			{
				for (int ii = 0; ii < 10; ii++)
				{
					hitMap[i][ii] = 0;
					pathMap[i][ii] = 0;
				}
			}
			pathMap[hunter.y][hunter.x] = 1;
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
					cc[i][ii] = pathMap[i][ii];
				}
			}
			int t = Finder(aa, bb, cc);
			if (t != 0)
			{
				while (t > 2)
				{
					for (int i = 0; i < 10; i++)
					{
						for (int ii = 0; ii < 10; ii++)
						{
							if (cc[i][ii] == t && aa[i][ii] == 2)
							{
								if (cc[i + 1][ii] == t - 1)
								{
									aa[i + 1][ii] = 2;
								}
								else if(cc[i - 1][ii] == t - 1)
								{
									aa[i - 1][ii] = 2;
								}
								else if (cc[i][ii + 1] == t - 1)
								{
									aa[i][ii + 1] = 2;
								}
								else if (cc[i][ii - 1] == t - 1)
								{
									aa[i][ii - 1] = 2;
								}
							}
						}
					}
					t--;
				}
			}
			
			for (int i = 0; i < 10; i++)
			{
				for (int ii = 0; ii < 10; ii++)
				{
					hitMap[i][ii] = aa[i][ii];
					findMap[i][ii] = bb[i][ii];
					pathMap[i][ii] = cc[i][ii];
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
				//_itoa_s(pathMap[a][i], keyHold, 10);
				//DrawString(keyHold, (tileSize * i), maxWidth - (tileSize * a) - 22, SColour(200, 200, 255, 255));
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