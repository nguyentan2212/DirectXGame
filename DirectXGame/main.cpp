#include <Windows.h>
#include "Core/GameEngine.h"
#include "Game/Scenes/CSceneOne.h"
#include "Game/Scenes/CSceneWorldMap.h"

#ifndef UNICODE
#define UNICODE
#endif

#define SCENE_WORLD_MAP "Assets/Tilemaps/world-map.json"
#define SCENE_ONE "Assets/Tilemaps/stage-1.json"

int WINAPI wWinMain(HINSTANCE hInstance, HINSTANCE, PWSTR pCmdLine, int nCmdShow)
{

	// Register the window class.
	GameEngine* app = GameEngine::GetInstance();
	app->Init(hInstance, nCmdShow);
	app->AddScene(new CSceneWorldMap(SCENE_WORLD_MAP));
	app->Run();

	return 0;
}