#include "AIE.h"
#include "KeyStater.h"
#include "Graph.h"

using namespace std;

//MOVE ME TO A CLASS

int maxWidth = 500;
int maxHeight = 500;
void Load(), Update(), Draw();
KeyStater Keys;
Graph theGraph(5);

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
	}
	
	void Update()
	{
		Keys.Update();

	}

	void Draw()
	{




		char mousex[10], mousey[10];
		_itoa_s(Keys.curs.x, mousex, 10);
		_itoa_s(Keys.curs.y, mousey, 10);
		DrawString(mousey, 400, 400, SColour(129, 129, 129, 255));
		DrawString(mousex, 350, 350, SColour(129, 129, 129, 255));
		Keys.Debug();
		ClearScreen();

	}