#include "Graph.h"

using namespace std;

Graph theGraph(graphW, graphH, graphX, graphY,tileSize);
KeyStater Keys;

int main(int argc, char* argv[])
{
	Load();
	//Game Loop
	do
	{
		if (Keys.IsPressed(VK_ESCAPE))
			return 0;
		Update();
		Draw();
	} while (!FrameworkUpdate());

	Shutdown();

	return 0;

}

	void Load()
	{
		Initialise(maxWidth, maxHeight, false, "PATHING");
		SetFont("./fonts/arial.fnt");
		SetBackgroundColour(SColour(0, 0, 0, 255));
		Keys.Initialize();
		CreateSprite("./images/good.png", tileSize - 1, tileSize - 1, false, SColour(255, 255, 255, 255));
		CreateSprite("./images/bad.png", tileSize - 1, tileSize - 1, false, SColour(255, 255, 255, 255));
	}
	
	void Update()
	{
		Keys.Update();
		if (Keys.IsPressed(VK_K))
		{
			theGraph.IsKill();
		}
		if (Keys.IsPressed(VK_L))
		{
			if (theGraph.SearchDFS(theGraph.mNodes[1], theGraph.mNodes[10]))
			{

			}
		}
		if (Keys.IsPressed(VK_O))
		{
			int i = 0;
		}
		if (Keys.IsPressed(VK_LBUTTON))
		{
			theGraph.TurnWall(theGraph.mNodes[(int)((((int)(Keys.curs.y -  graphY)/tileSize) * graphW) + ((Keys.curs.x - graphX)/tileSize ))]);
		}
	}

	void Draw()
	{
		theGraph.Draw();

		char mousex[10], mousey[10];
		_itoa_s(Keys.curs.x, mousex, 10);
		_itoa_s(Keys.curs.y, mousey, 10);
		DrawString(mousey, 400, 400, SColour(129, 129, 129, 255));
		DrawString(mousex, 350, 350, SColour(129, 129, 129, 255));
		Keys.Debug();
		ClearScreen();
	}
