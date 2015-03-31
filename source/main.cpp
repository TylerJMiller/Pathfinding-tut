#include "Graph.h"
#include "Tank.h"
#include "Wander.h"

using namespace std;

Graph theGraph(GRAPHWIDTH, GRAPHHEIGHT, GRAPHX, GRAPHY, TILESIZE);
KeyStater Keys;
Tank theTank;
Hunter theHunter;
Wander theWander;
double SINCELASTFRAME;

int main(int argc, char* argv[])
{
	Load();
	//Game Loop
	do
	{
		SINCELASTFRAME += GetDeltaTime();
		if (Keys.IsPressed(VK_ESCAPE))
			return 0;
		if (SINCELASTFRAME > 0.008f)
		{
			SINCELASTFRAME -= 0.016f;
			Update();
		}
		Draw();
	} while (!FrameworkUpdate());

	Shutdown();

	return 0;

}

	void Load()
	{
		SINCELASTFRAME = 0;
		Initialise(WINDOWWIDTH, WINDOWHEIGHT, false, "PATHING");
		SetFont("./fonts/arial.fnt");
		SetBackgroundColour(SColour(0, 0, 0, 255));
		Keys.Initialize();
		CreateSprite("./images/good.png", TILESIZE - 1, TILESIZE - 1, false, SColour(255, 255, 255, 255));
		CreateSprite("./images/bad.png", TILESIZE - 1, TILESIZE - 1, false, SColour(255, 255, 255, 255));
		CreateSprite("./images/walked.png", TILESIZE - 1, TILESIZE - 1, false, SColour(255, 255, 255, 255));
		CreateSprite("./images/end.png", TILESIZE - 1, TILESIZE - 1, false, SColour(255, 255, 255, 255));
		theTank = Tank(0, 0, CreateSprite("./images/start.png", TILESIZE / 2, TILESIZE / 2, false, SColour(255, 255, 255, 255)));
		theHunter = Hunter(CreateSprite("./images/hunter.png", 30, 30, false, SColour(255, 255, 255, 255)), 500, 500, 1);
		theWander = Wander(CreateSprite("./images/wander.png", 30, 30, false, SColour(255, 255, 255, 255)), 300, 300, 3, .1f);
	}
	
	void Update()
	{
		Keys.Update();

		theHunter.Update();
		theWander.Update();
		if (Keys.IsPressed(VK_K))
		{
			theGraph.ResetVisited();
			theGraph.SearchSTAR(theGraph.mNodes[theTank.nodeNum()], theGraph.mNodes[(GRAPHHEIGHT * GRAPHWIDTH) - 1]);
			//theGraph.Dijkstra(theGraph.mNodes[theTank.nodeNum()], theGraph.mNodes[(graphH * graphW) - 1]);
		}
		if (Keys.IsPressed(VK_L))
		{
			theGraph.ResetVisited();
			if (theGraph.SearchDFS(theGraph.mNodes[theTank.nodeNum()], theGraph.mNodes[(GRAPHHEIGHT * GRAPHWIDTH) - 1]))
			{
				theGraph.Dijkstra(theGraph.mNodes[theTank.nodeNum()], theGraph.mNodes[(GRAPHHEIGHT * GRAPHWIDTH) - 1]);
			}
		}
		if (Keys.IsPressed(VK_I))
		{
			theGraph.ResetVisited();
		}
		/*if (Keys.IsPressed(VK_O))
		{
			int i = theGraph.DistanceTo(theGraph.mNodes[0], theGraph.mNodes[theGraph.mNodes.size() - 1]);
			i = i;
		}*/

		//if (Keys.IsDown(VK_P))
		//{
			theHunter.SetTarget(theWander.GetPosVec());
		//}
		if (Keys.IsPressed(VK_M))
		{
			theHunter.ToggleDraw();
		}
		if (Keys.IsPressed(VK_N))
		{
			theWander.ToggleWander();
		}
		if (Keys.IsPressed(VK_LBUTTON))
		{
			if (Keys.curs.y > GRAPHY - TILESIZE && Keys.curs.y < GRAPHY + (TILESIZE * (GRAPHHEIGHT)) - TILESIZE &&  Keys.curs.x > GRAPHX && Keys.curs.x < GRAPHY + (TILESIZE * GRAPHWIDTH))
				theTank.move(Keys.curs.x,Keys.curs.y);
		}
		if (Keys.IsDown(VK_RBUTTON))
		{
			if (Keys.curs.y > GRAPHY - TILESIZE && Keys.curs.y < GRAPHY + (TILESIZE * (GRAPHHEIGHT)) - TILESIZE &&  Keys.curs.x > GRAPHX && Keys.curs.x < GRAPHY + (TILESIZE * GRAPHWIDTH))
				theGraph.TurnWall(theGraph.mNodes[(int)((((Keys.curs.y - (GRAPHY - TILESIZE)) / TILESIZE) * GRAPHWIDTH) + ((Keys.curs.x - GRAPHX) / TILESIZE))]);
		}
	}

	void Draw()
	{
		theGraph.Draw();
		theTank.Draw();
		theHunter.Draw();
		theWander.Draw();
		char mousex[10], mousey[10];
		_itoa_s(Keys.curs.x, mousex, 10);
		_itoa_s(Keys.curs.y, mousey, 10);
		DrawString(mousey, 400, 400, SColour(129, 129, 129, 255));
		DrawString(mousex, 350, 350, SColour(129, 129, 129, 255));
		Keys.Debug();
		ClearScreen();
	}
