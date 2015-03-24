#include "KeyStater.h"
#include "AIE.h"
#include "Util.h"

KeyStater::KeyStater()
{
	GetKeyboardState(curStates);
	for (int i = 0; i < 256; i++)
	{
		oldStates[i] = curStates[i];
	}
	GetCursorPos(&curs);
	ScreenToClient(thiswindow, &curs);
}

KeyStater::~KeyStater()
{
}

void KeyStater::Initialize()
{
	thiswindow = GetForegroundWindow();
}

void KeyStater::Update()
{
	for (int i = 0; i < 256; i++)
	{
		oldStates[i] = curStates[i];
	}
	GetKeyboardState(curStates);
	GetCursorPos(&curs);
	ScreenToClient(thiswindow, &curs);
	curs.y = maxHeight - curs.y;
}

void KeyStater::Debug()
{
	if (IsPressed(VK_F5))
		showDebug = !showDebug;

	if (showDebug)
	{
		for (int i = 0; i < 16; i++)
		{
			for (int a = 0; a < 16; a++)
			{
				char keyhold[10];
				_itoa_s(curStates[(i * 16) + a], keyhold, 10);
				DrawString(keyhold, i * 20, (a * 20) + 40, SColour(125, 125, 125, 255));				//CREATE DRAWSTRING FUNC
			}
		}
	}
}

bool KeyStater::IsUp(int key)
{
	if (curStates[key] < 2 && oldStates[key] < 2)
		return true;
	return false;
}
bool KeyStater::IsDown(int key)
{
	if (curStates[key] > 2 && oldStates[key] > 2)
		return true;
	return false;
}
bool KeyStater::IsToggledOn(int key)
{
	if (curStates[key] == 1)
		return true;
	return false;
}
bool KeyStater::IsPressed(int key)
{
	if (curStates[key] > 2 && oldStates[key] < 2)
		return true;
	return false;
}
bool KeyStater::IsReleased(int key)
{
	if (curStates[key] < 2 && oldStates[key] > 2)
		return true;
	return false;
}