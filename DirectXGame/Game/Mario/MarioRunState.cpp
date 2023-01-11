#include "MarioRunState.h"
#include "MarioJumpState.h"
#include "MarioIdleState.h"
#include "MarioSitState.h"
#include "MarioRunAndHoldState.h"
#include "Mario.h"
#include "MarioFlyState.h"
#include "MarioKickState.h"
#include "MarioAttackState.h"
#include <dinput.h>

MarioRunState::MarioRunState(int direction): State()
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
			float direction = this->_context->velocity.x < 0 ? -1.0f : 1.0f;
			float v = max(MARIO_RUN_MAX_SPEED_X / 2.0f, abs(this->_context->velocity.x));
			this->_context->velocity = VECTOR2D(v * direction, this->_context->velocity.y);
			this->_context->TransitionTo(new MarioJumpState(MARIO_RUN_JUMP_SPEED_FACTOR_Y));
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
	else if (keyCode == DIK_A && this->_context->name == "raccoon mario")
	{
		Mario* mario = dynamic_cast<Mario*>(this->_context);
		mario->UpdateRunSpeed(0.0f);
		this->_context->TransitionTo(new MarioAttackState());
	}
}

void MarioRunState::OnKeyUp(int keyCode)
{
	if (keyCode == DIK_LEFT || keyCode == DIK_RIGHT)
	{
		Mario* mario = dynamic_cast<Mario*>(this->_context);
		mario->UpdateRunSpeed(0.0f);
		this->_context->velocity = VECTOR2D(0.0f, 0.0f);
		this->_context->TransitionTo(new MarioIdleState());
	}
	else if (keyCode == DIK_K)
	{
		this->_context->TransitionTo(new MarioKickState());
	}
}

void MarioRunState::Update(float deltaTime)
{
	if (this->_context->name == "raccoon mario")
	{
		Mario* mario = dynamic_cast<Mario*>(this->_context);
		mario->UpdateRunSpeed(this->_context->velocity.x);

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
