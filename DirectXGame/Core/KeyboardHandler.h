#pragma once
#include <list>
#include <d3d10.h>
#include <dinput.h>
#include "GameObject.h"

#define DIRECTINPUT_VERSION 0x0800
#define KEYBOARD_BUFFER_SIZE 1024
#define KEYBOARD_STATE_SIZE 256

using namespace::std;

class KeyboardHandler
{
public:
	KeyboardHandler(HINSTANCE hInstance, HWND hwnd);
	~KeyboardHandler();

	void Processing();
	void AddListener(GameObject* listener);
	void RemoveListener(GameObject* listener);

private:
	LPDIRECTINPUT8       _di;		// The DirectInput object         
	LPDIRECTINPUTDEVICE8 _didv;		// The keyboard device 

	BYTE  _keyStates[KEYBOARD_STATE_SIZE];			// DirectInput keyboard state buffer 
	DIDEVICEOBJECTDATA _keyEvents[KEYBOARD_BUFFER_SIZE];		// Buffered keyboard data

	list<GameObject*> _listeners;
	void OnKeyUp(int keyCode);
	void OnKeyDown(int keyCode);
};

