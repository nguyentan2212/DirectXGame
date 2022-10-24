#include <Windows.h>
#include "Core/GameEngine.h"
#include "Game/Scenes/CSceneOne.h"

#ifndef UNICODE
#define UNICODE
#endif

#define SCENE_ONE "Assets/Tilemaps/stage-1.json"

int WINAPI wWinMain(HINSTANCE hInstance, HINSTANCE, PWSTR pCmdLine, int nCmdShow)
{

	// Register the window class.
	GameEngine* app = GameEngine::GetInstance();
	app->Init(hInstance, nCmdShow);
	app->AddScene(new CSceneOne(SCENE_ONE));
	app->Run();

	return 0;
}