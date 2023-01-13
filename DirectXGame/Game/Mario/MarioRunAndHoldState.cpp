#include "MarioRunAndHoldState.h"
#include <dinput.h>
#include "MarioRunState.h"
#include "MarioHoldState.h"
#include "../../Core/GameObject.h"
#include "MarioConst.h"

MarioRunAndHoldState::MarioRunAndHoldState(int direction)
{
	this->_name = "run and hold";
	DebugOut((wchar_t*)L"[INFO] Mario transition to Run and Hold State \n");
	//init logic
	this->direction = direction;
}

void MarioRunAndHoldState::OnTransition()
{
	if (direction == 0)// prev direction
	{
		direction = this->_context->velocity.x > 0 ? 1 : -1;
	}

	this->_context->acceleration = VECTOR2D(direction * MARIO_X_ACCE, this->_context->acceleration.y);
}

void MarioRunAndHoldState::OnKeyDown(int keyCode)
{
	if (keyCode == DIK_H)
	{
		this->_context->TransitionTo(new MarioRunState(0));
	}
}

void MarioRunAndHoldState::OnKeyUp(int keyCode)
{
	if (keyCode == DIK_LEFT || keyCode == DIK_RIGHT)
	{
		this->_context->TransitionTo(new MarioHoldState());
	}
}