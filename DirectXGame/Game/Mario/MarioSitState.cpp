#include "MarioSitState.h"
#include "../../Core/GameObject.h"
#include "MarioIdleState.h"
#include <dinput.h>

MarioSitState::MarioSitState(): ObjectState()
{
	this->_width = 16.0f;
	this->_height = 24.0f;
	this->_name = "sit";
	DebugOut((wchar_t*)L"[INFO] Mario transition to Sit State \n");
}

void MarioSitState::OnKeyUp(int keyCode)
{
	if (keyCode == DIK_DOWN)
	{
		this->_context->TransitionTo(new MarioIdleState());
	}
}
