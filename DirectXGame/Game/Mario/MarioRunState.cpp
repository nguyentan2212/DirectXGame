#include "MarioRunState.h"
#include "MarioJumpState.h"
#include "MarioIdleState.h"
#include "MarioSitState.h"
#include "MarioRunAndHoldState.h"
#include "Mario.h"
#include "MarioFlyState.h"
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
		if (this->_context->name == "raccoon mario" && this->_name == "fast run")
		{
			this->_context->TransitionTo(new MarioFlyState());
		}
		else
		{
			this->_context->TransitionTo(new MarioJumpState());
		}
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

void MarioRunState::OnChangeFigure()
{
	if (this->_context->name == "small mario")
	{
		this->_context->width = 15.0f;
		this->_context->height = 16.0f;
	}
	else if (this->_context->name == "super mario")
	{
		this->_context->width = 16.0f;
		this->_context->height = 28.0f;
	}
	else if (this->_context->name == "raccoon mario")
	{
		this->_context->width = 21.0f;
		this->_context->height = 28.0f;
	}
	// fast run -> w: 24, h: 28
}

void MarioRunState::Update(float deltaTime)
{
	if (this->_context->name == "raccoon mario")
	{
		if (abs(this->_context->velocity.x) >= MARIO_RUN_MAX_SPEED_X)
		{
			this->_name = "fast run";
		}
		else
		{
			this->_name = "run";
		}
	}
}
