#include "MarioRunAndHoldState.h"
#include <dinput.h>
#include "MarioRunState.h"
#include "MarioHoldState.h"
#include "../../Core/GameObject.h"
#include "Mario.h"

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

void MarioRunAndHoldState::OnChangeFigure()
{
	if (this->_context->name == "small mario")
	{
		this->_context->width = 15.0f;
		this->_context->height = 16.0f;
	}
	else if (this->_context->name == "super mario")
	{
		this->_context->width = 16.0f;
		this->_context->height = 32.0f;
	}
	else if (this->_context->name == "raccoon mario")
	{
		this->_context->width = 22.0f;
		this->_context->height = 28.0f;
	}
}
