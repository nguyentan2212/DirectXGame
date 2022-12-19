#include "MarioRunState.h"
#include "../../Core/GameObject.h"
#include "MarioJumpState.h"
#include "MarioIdleState.h"
#include "MarioSitState.h"
#include "MarioRunAndHoldState.h"
#include "Mario.h"
#include <dinput.h>

MarioRunState::MarioRunState(int direction): ObjectState()
{
	this->_name = "run";
    DebugOut((wchar_t*)L"[INFO] Mario transition to Run State \n");
	// init logic
	this->direction = direction;
}

void MarioRunState::OnTransition()
{
	if (this->_context->name == "small mario")
	{
		this->_width = 15.0f;
		this->_height = 16.0f;
	}
	else
	{
		this->_width = 16.0f;
		this->_height = 32.0f;
	}
	if (direction == 0)// prev direction
	{
		direction = this->_context->velocity.x > 0 ? 1 : -1;
	}

	this->_context->acceleration = VECTOR2D(direction * MARIO_X_ACCE, 0.0f);
}

void MarioRunState::OnCollision(CollisionEvent colEvent)
{
}

void MarioRunState::OnKeyDown(int keyCode)
{
	if (keyCode == DIK_UP)
	{
		this->_context->TransitionTo(new MarioJumpState());
	}
	else if (keyCode == DIK_DOWN)
	{
		this->_context->TransitionTo(new MarioSitState());
	}
	else if (keyCode == DIK_H)
	{
		this->_context->TransitionTo(new MarioRunAndHoldState(0));
	}
}

void MarioRunState::OnKeyUp(int keyCode)
{
	if (keyCode == DIK_LEFT || keyCode == DIK_RIGHT)
	{
		this->_context->velocity = VECTOR2D(0.0f, 0.0f);
		this->_context->TransitionTo(new MarioIdleState());
	}
}
