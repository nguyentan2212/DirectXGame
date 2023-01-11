#include "MarioIdleState.h"
#include "../../Core/GameObject.h"
#include "MarioRunState.h"
#include "MarioJumpState.h"
#include "MarioFallState.h"
#include <dinput.h>

MarioIdleState::MarioIdleState()
{
	this->_name = "idle";
	DebugOut((wchar_t*)L"[INFO] Mario transition to Idle State \n");
}

void MarioIdleState::Update(float deltaTime)
{
	if (this->_context->isGrounded == false)
	{
		this->_context->TransitionTo(new MarioFallState());
	}
}

void MarioIdleState::OnTransition()
{
	this->_context->velocity = VECTOR2D(0.0f, 0.0f);
	this->_context->acceleration = VECTOR2D(0.0f, 0.0f);
}

void MarioIdleState::OnKeyDown(int keyCode)
{
	switch (keyCode)
	{
	case DIK_UP:
		this->_context->TransitionTo(new MarioJumpState());
		break;
	case DIK_LEFT:
	case DIK_RIGHT:
	{
		int direction = (keyCode - DIK_LEFT) - 1;
		this->_context->TransitionTo(new MarioRunState(direction));
		break;
	}
	default:
		break;
	}
}