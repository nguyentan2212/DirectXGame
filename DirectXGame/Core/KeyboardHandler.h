#pragma once
#include <list>
#include <d3d10.h>
#include <dinput.h>
#include "GameObject.h"

constexpr auto DINPUT_VERSION = 0x0800;
constexpr int KEYBOARD_BUFFER_SIZE = 1024;
constexpr int KEYBOARD_STATE_SIZE = 256;

using namespace::std;

class KeyboardHandler
{
public:
	void Initialize(HINSTANCE hInstance, HWND hwnd);
	static KeyboardHandler* GetInstance();
	~KeyboardHandler();

	void Processing();
	void AddListener(GameObject* listener);
	void RemoveListener(GameObject* listener);

private:
	KeyboardHandler();
	LPDIRECTINPUT8       _di;		// The DirectInput object         
	LPDIRECTINPUTDEVICE8 _didv;		// The keyboard device 

	BYTE  _keyStates[KEYBOARD_STATE_SIZE];			// DirectInput keyboard state buffer 
	DIDEVICEOBJECTDATA _keyEvents[KEYBOARD_BUFFER_SIZE];		// Buffered keyboard data

	list<GameObject*> _listeners;
	void OnKeyUp(int keyCode);
	void OnKeyDown(int keyCode);
	static KeyboardHandler* _instance;
};

