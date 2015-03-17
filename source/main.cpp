#include "Graph.h"
#include "KeyStater.h"

using namespace std;

//MOVE ME TO A CLASS

int maxWidth = 500;
int maxHeight = 500;
void Load(), Update(), Draw();
Graph theGraph(4,6,100,100,50);
KeyStater Keys;
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
		CreateSprite("./images/good.png", 49, 49, false, SColour(255, 255, 255, 255));
		CreateSprite("./images/bad.png", 49, 49, false, SColour(255, 255, 255, 255));
		//theGraph.AddNode(GraphNode())
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
			theGraph.SearchDFS(theGraph.mNodes[0], theGraph.mNodes[2]);
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