#include <Windows.h>
#include "Core/GameEngine.h"
#include "Game/Scenes/CSceneOne.h"
#include "Game/Scenes/CSceneWorldMap.h"
#include "Game/Scenes/CSceneHidden.h"

#ifndef UNICODE
#define UNICODE
#endif

int WINAPI wWinMain(HINSTANCE hInstance, HINSTANCE, PWSTR pCmdLine, int nCmdShow)
{

	// Register the window class.
	GameEngine* app = GameEngine::GetInstance();
	app->Init(hInstance, nCmdShow);
	app->AddScene(new CSceneOne(), SCENE_ONE_ID);
	app->AddScene(new CSceneHidden(), SCENE_HIDDEN_ID);
	app->TransitionTo(SCENE_ONE_ID);
	//app->TransitionTo(SCENE_HIDDEN_ID);
	app->Run();

	return 0;
}