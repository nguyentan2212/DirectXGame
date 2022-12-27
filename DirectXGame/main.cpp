#include <Windows.h>
#include "Core/GameEngine.h"
#include "Game/Scenes/CSceneOne.h"
#include "Game/Scenes/CSceneWorldMap.h"

#ifndef UNICODE
#define UNICODE
#endif

int WINAPI wWinMain(HINSTANCE hInstance, HINSTANCE, PWSTR pCmdLine, int nCmdShow)
{

	// Register the window class.
	GameEngine* app = GameEngine::GetInstance();
	app->Init(hInstance, nCmdShow);
	app->TransitionTo(new CSceneWorldMap());
	app->Run();

	return 0;
}