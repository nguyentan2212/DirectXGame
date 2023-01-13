#include "MarioDeathState.h"
#include "../../Core/GameObject.h"
#include "MarioConst.h"

MarioDeathState::MarioDeathState()
{
	this->_name = "death";
	DebugOut((wchar_t*)L"[INFO] Mario transition to Death State \n");
}

void MarioDeathState::Update(float deltaTime)
{
	VECTOR2D pos = this->_context->GetWorldPosition();
	if (pos.y <= -40.0f)
	{
		this->_context->isActive = false;
	}
}

void MarioDeathState::OnTransition()
{
	this->_context->velocity = VECTOR2D(0.0f, MARIO_JUMP_SPEED_Y);
	this->_context->acceleration = VECTOR2D(0.0f, -MARIO_GRAVITY * 1.5f);
	this->_context->width = 16.0f;
	this->_context->height = 16.0f;
}
