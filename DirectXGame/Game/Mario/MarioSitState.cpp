#include "MarioSitState.h"
#include "../../Core/GameObject.h"
#include "MarioIdleState.h"
#include <dinput.h>

MarioSitState::MarioSitState(): ObjectState()
{
	this->_width = 16.0f;
	this->_height = 24.0f;
	this->_name = "sit";
	DebugOut((wchar_t*)L"[INFO] Mario transition to Sit State \n");
}

void MarioSitState::OnTransition()
{
	this->_context->velocity = VECTOR2D(0.0f, 0.0f);
	this->_context->acceleration = VECTOR2D(0.0f, 0.0f);
	this->_context->position = VECTOR2D(this->_context->position.x, this->_context->position.y - 4.0f);
}

void MarioSitState::OnKeyUp(int keyCode)
{
	if (keyCode == DIK_DOWN)
	{
		this->_context->position = VECTOR2D(this->_context->position.x, this->_context->position.y + 4.0f);
		this->_context->TransitionTo(new MarioIdleState());
	}
}
