#include "MarioIdleState.h"
#include "../../Core/GameObject.h"
#include "MarioRunState.h"
#include "MarioJumpState.h"
#include "MarioSitState.h"
#include "MarioKickState.h"
#include "MarioHoldState.h"
#include "MarioAttackState.h"
#include "Mario.h"
#include <dinput.h>

MarioIdleState::MarioIdleState()
{
	this->_name = "idle";
	DebugOut((wchar_t*)L"[INFO] Mario transition to Idle State \n");
}

void MarioIdleState::OnTransition()
{
	this->_context->velocity = VECTOR2D(0.0f, 0.0f);
	this->_context->acceleration = VECTOR2D(0.0f, 0.0f);

	if (this->_context->name == "small mario")
	{
		this->_context->width = 16.0f;
		this->_context->height = 16.0f;
	}
	else if (this->_context->name == "super mario")
	{
		this->_context->width = 16.0f;
		this->_context->height = 28.0f;
	}
	else if (this->_context->name == "raccoon mario")
	{
		this->_context->width = 23.0f;
		this->_context->height = 27.0f;
	}
}

void MarioIdleState::OnKeyDown(int keyCode)
{
	switch (keyCode)
	{
	case DIK_UP:
		this->_context->TransitionTo(new MarioJumpState());
		break;
	case DIK_DOWN:
		if (this->_context->name != "small mario")
		{
			this->_context->TransitionTo(new MarioSitState());
		}
		break;
	case DIK_LEFT:
	case DIK_RIGHT:
	{
		int direction = (keyCode - DIK_LEFT) - 1;
		this->_context->TransitionTo(new MarioRunState(direction));
	}
		break;
	case DIK_K:
		this->_context->TransitionTo(new MarioKickState());
		break;
	case DIK_H:
		this->_context->TransitionTo(new MarioHoldState());
		break;
	case DIK_A:
		if (this->_context->name == "raccoon mario")
		{
			this->_context->TransitionTo(new MarioAttackState());
		}
		break;
	default:
		break;
	}
}