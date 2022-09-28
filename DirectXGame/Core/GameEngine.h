#pragma once
#include <Windows.h>
#include "Timer.h"

#define FPS 60
#define WINDDOW_WIDTH 600
#define WINDOW_HEIGHT 400
#define GAME_TITLE L"My Game"

class GameEngine
{
public:
	static GameEngine* GetInstance();
	void Init(HINSTANCE hInstance, int nCmdShow);

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
	float _width = WINDDOW_WIDTH, _height = WINDOW_HEIGHT;
	const float _fps = FPS;

	static GameEngine* _instance;
};

