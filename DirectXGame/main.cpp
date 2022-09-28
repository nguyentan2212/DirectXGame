#include <Windows.h>
#include "Core/GameEngine.h"

#ifndef UNICODE
#define UNICODE
#endif

int WINAPI wWinMain(HINSTANCE hInstance, HINSTANCE, PWSTR pCmdLine, int nCmdShow)
{

	// Register the window class.
	GameEngine* app = GameEngine::GetInstance();
	app->Init(hInstance, nCmdShow);
	app->Run();

	return 0;
}