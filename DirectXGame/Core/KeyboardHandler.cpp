#include "KeyboardHandler.h"
#include "../Utils/Debug.h"

KeyboardHandler* KeyboardHandler::_instance = nullptr;

KeyboardHandler::KeyboardHandler()
{
	
}

void KeyboardHandler::Initialize(HINSTANCE hInstance, HWND hwnd)
{
	HRESULT hr = DirectInput8Create(hInstance,
		DINPUT_VERSION,
		IID_IDirectInput8,
		(VOID**)&this->_di,
		NULL);

	if (hr != DI_OK)
	{
		DebugOut(L"[ERROR] DirectInput8Create failed!\n");
		return;
	}

	hr = this->_di->CreateDevice(GUID_SysKeyboard, &this->_didv, NULL);
	if (hr != DI_OK)
	{
		DebugOut(L"[ERROR] CreateDevice failed!\n");
		return;
	}

	this->_didv->SetDataFormat(&c_dfDIKeyboard);
	this->_didv->SetCooperativeLevel(hwnd, DISCL_FOREGROUND | DISCL_NONEXCLUSIVE);

	DIPROPDWORD dipdw;
	dipdw.diph.dwSize = sizeof(DIPROPDWORD);
	dipdw.diph.dwHeaderSize = sizeof(DIPROPHEADER);
	dipdw.diph.dwObj = 0;
	dipdw.diph.dwHow = DIPH_DEVICE;
	dipdw.dwData = KEYBOARD_BUFFER_SIZE;

	hr = this->_didv->SetProperty(DIPROP_BUFFERSIZE, &dipdw.diph);

	hr = this->_didv->Acquire();
	if (hr != DI_OK)
	{
		DebugOut(L"[ERROR] DINPUT8::Acquire failed!\n");
		return;
	}

	DebugOut(L"[INFO] Keyboard has been initialized successfully\n");
}

KeyboardHandler* KeyboardHandler::GetInstance()
{
	if (_instance == nullptr)
	{
		_instance = new KeyboardHandler();
	}
	return _instance;
}

void KeyboardHandler::Processing()
{
	HRESULT hr = this->_didv->GetDeviceState(sizeof(this->_keyStates), this->_keyStates);
	if (FAILED(hr))
	{
		// If the keyboard lost focus or was not acquired then try to get control back.
		if ((hr == DIERR_INPUTLOST) || (hr == DIERR_NOTACQUIRED))
		{
			HRESULT h = this->_didv->Acquire();
			if (h == DI_OK)
			{
				DebugOut(L"[INFO] Keyboard re-acquired!\n");
			}
			else return;
		}
		else
		{
			DebugOut(L"[ERROR] DINPUT::GetDeviceState failed. Error: %d\n", hr);
			return;
		}
	}

	// Collect all buffered events
	DWORD dwElements = KEYBOARD_BUFFER_SIZE;
	hr = this->_didv->GetDeviceData(sizeof(DIDEVICEOBJECTDATA), this->_keyEvents, &dwElements, 0);
	if (FAILED(hr))
	{
		DebugOut(L"[ERROR] DINPUT::GetDeviceData failed. Error: %d\n", hr);
		return;
	}

	// Scan through all buffered events, check if the key is pressed or released
	for (DWORD i = 0; i < dwElements; i++)
	{
		int keyCode = this->_keyEvents[i].dwOfs;
		int keyState = this->_keyEvents[i].dwData;
		if ((keyState & 0x80) > 0)
		{
			OnKeyDown(keyCode);
		}
		else
		{
			OnKeyUp(keyCode);
		}
	}
}

void KeyboardHandler::AddListener(GameObject* listener)
{
	this->_listeners.push_back(listener);
}

void KeyboardHandler::RemoveListener(GameObject* listener)
{
	this->_listeners.remove(listener);
}

void KeyboardHandler::OnKeyUp(int keyCode)
{
	for (GameObject* obj : this->_listeners)
	{
		obj->OnKeyUp(keyCode);
	}
}

void KeyboardHandler::OnKeyDown(int keyCode)
{
	for (GameObject* obj : this->_listeners)
	{
		obj->OnKeyDown(keyCode);
	}
}

KeyboardHandler::~KeyboardHandler()
{
	this->_di->Release();
	this->_didv->Release();
}
