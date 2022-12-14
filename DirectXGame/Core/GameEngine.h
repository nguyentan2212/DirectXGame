#pragma once
#include <vector>
#include <Windows.h>
#include <string>
#include "Timer.h"
#include "GameObject.h"

#define FPS 60
#define WINDOW_WIDTH 300
#define WINDOW_HEIGHT 200
#define GAME_TITLE L"My Name"
#define DEFAULT_CONFIG "Assets/config.json"

using namespace::std;

class Scene;
class GameEngine
{
public:
	static GameEngine* GetInstance();
	void Init(HINSTANCE hInstance, int nCmdShow);

	void TransitionTo(Scene* scene);
	void Run();
private:
	GameEngine();
	~GameEngine();

	void Update(float deltaTime);
	void Render();

	void CreateGameWindow(int nCmdShow);
	bool ProcessMessages();

	HINSTANCE _hInstance;
	HWND _hwnd;
	Timer* _timer;

	int _width = WINDOW_WIDTH, _height = WINDOW_HEIGHT;
	float _fps = FPS;

	Scene* _currentScene;

	static GameEngine* _instance;
};

