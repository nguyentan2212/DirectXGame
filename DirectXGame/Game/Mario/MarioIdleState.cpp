#include "MarioIdleState.h"
#include "../../Graphic/AnimationService.h"
#include "../../Core/GameObject.h"
#include "MarioRunState.h"
#include "MarioJumpState.h"
#include "MarioSitState.h"
#include <dinput.h>

MarioIdleState::MarioIdleState()
{
	AnimationService* animations = AnimationService::GetInstance();
	// this->_animation = animations->GetAnimation("super mario idle");

	this->_width = 16.0f;
	this->_height = 32.0f;
	this->_name = "idle";
	DebugOut((wchar_t*)L"[INFO] Mario transition to Idle State \n");
}

void MarioIdleState::OnKeyDown(int keyCode)
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
