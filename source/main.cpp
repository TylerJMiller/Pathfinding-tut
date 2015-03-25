#include "Graph.h"
#include "Tank.h"

using namespace std;

Graph theGraph(graphW, graphH, graphX, graphY,tileSize);
KeyStater Keys;
Tank theTank;

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
		CreateSprite("./images/walked.png", tileSize - 1, tileSize - 1, false, SColour(255,255,255,255));
		CreateSprite("./images/end.png", tileSize - 1, tileSize - 1, false, SColour(255, 255, 255, 255));
		theTank.init(0, 0, CreateSprite("./images/start.png", tileSize/2, tileSize/2, false, SColour(255, 255, 255, 255)));
	}
	
	void Update()
	{
		Keys.Update();
		if (Keys.IsPressed(VK_K))
		{
			if (theGraph.SearchSTAR(theGraph.mNodes[theTank.nodeNum()], theGraph.mNodes[(graphH * graphW) - 1]))
			{

			}
		}
		if (Keys.IsPressed(VK_L))
		{
			if (theGraph.SearchDFS(theGraph.mNodes[theTank.nodeNum()], theGraph.mNodes[(graphH * graphW) - 1]))
			{
				theGraph.Dijkstra(theGraph.mNodes[theTank.nodeNum()], theGraph.mNodes[(graphH * graphW) - 1]);
			}
		}
		if (Keys.IsPressed(VK_O))
		{
			int i = 0;
		}
		if (Keys.IsPressed(VK_I))
		{
			theGraph.ResetVisited();
		}
		if (Keys.IsPressed(VK_LBUTTON))
		{
			if (Keys.curs.y > graphY - tileSize && Keys.curs.y < graphY + (tileSize * (graphH)) - tileSize &&  Keys.curs.x > graphX && Keys.curs.x < graphY + (tileSize * graphW))
				theTank.move(Keys.curs.x,Keys.curs.y);
		}
		if (Keys.IsDown(VK_RBUTTON))
		{
			if (Keys.curs.y > graphY - tileSize && Keys.curs.y < graphY + (tileSize * (graphH)) - tileSize &&  Keys.curs.x > graphX && Keys.curs.x < graphY + (tileSize * graphW))
				theGraph.TurnWall(theGraph.mNodes[(int)((((Keys.curs.y -  (graphY - tileSize))/tileSize) * graphW) + ((Keys.curs.x - graphX)/tileSize ))]);
		}
	}

	void Draw()
	{
		theGraph.Draw();
		theTank.Draw();
		char mousex[10], mousey[10];
		_itoa_s(Keys.curs.x, mousex, 10);
		_itoa_s(Keys.curs.y, mousey, 10);
		DrawString(mousey, 400, 400, SColour(129, 129, 129, 255));
		DrawString(mousex, 350, 350, SColour(129, 129, 129, 255));
		Keys.Debug();
		ClearScreen();
	}
