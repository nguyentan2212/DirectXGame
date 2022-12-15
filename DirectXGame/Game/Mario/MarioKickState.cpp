#include "MarioKickState.h"
#include "MarioRunState.h"
#include "MarioJumpState.h"
#include "MarioSitState.h"
#include "MarioIdleState.h"
#include "../../Core/GameObject.h"
#include <dinput.h>

MarioKickState::MarioKickState()
{
	this->_width = 24.0f;
	this->_height = 32.0f;
	this->_name = "kick";
	DebugOut((wchar_t*)L"[INFO] Mario transition to Kick State \n");
}

void MarioKickState::OnKeyDown(int keyCode)
{
	if (keyCode == DIK_UP)
	{
		this->_context->velocity = VECTOR2D(0.0f, 100);
		this->_context->TransitionTo(new MarioJumpState());
	}
	else if (keyCode == DIK_DOWN)
	{
		this->_context->velocity = VECTOR2D(0.0f, 0.0f);
		this->_context->TransitionTo(new MarioSitState());
	}
	else if (keyCode == DIK_LEFT || keyCode == DIK_RIGHT)
	{
		int direction = (keyCode - DIK_LEFT) - 1;
		this->_context->velocity = VECTOR2D(direction * 50, 0.0f);
		this->_context->TransitionTo(new MarioRunState());
	}
}

void MarioKickState::OnKeyUp(int keyCode)
{
	if (keyCode == DIK_K)
	{
		this->_context->TransitionTo(new MarioIdleState());
	}
}
