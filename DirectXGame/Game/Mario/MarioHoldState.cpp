#include "MarioHoldState.h"
#include "MarioIdleState.h"
#include "MarioRunAndHoldState.h"
#include "../../Core/GameObject.h"
#include <dinput.h>

MarioHoldState::MarioHoldState()
{
	this->_name = "hold";
	DebugOut((wchar_t*)L"[INFO] Mario transition to Hold State \n");	
}

void MarioHoldState::OnTransition()
{
	if (this->_context->name == "small mario")
	{
		this->_width = 14.0f;
		this->_height = 16.0f;
	}
	else
	{
		this->_width = 16.0f;
		this->_height = 32.0f;
	}
	this->_context->velocity = VECTOR2D(0.0f, 0.0f);
	this->_context->acceleration = VECTOR2D(0.0f, 0.0f);
}

void MarioHoldState::OnKeyDown(int keyCode)
{
	if (keyCode == DIK_H)
	{
		this->_context->TransitionTo(new MarioIdleState());
	}
	else if (keyCode == DIK_LEFT || keyCode == DIK_RIGHT)
	{
		int direction = (keyCode - DIK_LEFT) - 1;
		this->_context->TransitionTo(new MarioRunAndHoldState(direction));
	}
}

void MarioHoldState::OnKeyUp(int keyCode)
{
}
