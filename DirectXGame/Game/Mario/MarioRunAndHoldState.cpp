#include "MarioRunAndHoldState.h"
#include <dinput.h>
#include "MarioRunState.h"
#include "MarioHoldState.h"
#include "../../Core/GameObject.h"

MarioRunAndHoldState::MarioRunAndHoldState()
{
	this->_width = 16.0f;
	this->_height = 32.0f;
	this->_name = "run and hold";
	DebugOut((wchar_t*)L"[INFO] Mario transition to Run and Hold State \n");
}

void MarioRunAndHoldState::OnKeyDown(int keyCode)
{
	if (keyCode == DIK_H)
	{
		this->_context->TransitionTo(new MarioRunState());
	}
}

void MarioRunAndHoldState::OnKeyUp(int keyCode)
{
	if (keyCode == DIK_LEFT || keyCode == DIK_RIGHT)
	{
		this->_context->velocity = VECTOR2D(0.0f, 0.0f);
		this->_context->TransitionTo(new MarioHoldState());
	}
}
