#include "MarioAttackState.h"
#include "MarioRunState.h"
#include "MarioIdleState.h"
#include "MarioFallState.h"
#include "../../Core/GameObject.h"
#include "../../Core/KeyboardHandler.h"
#include <dinput.h>

MarioAttackState::MarioAttackState()
{
	this->_name = "attack";
	this->_cooldown = ATTACK_COOLDOWN;
	DebugOut((wchar_t*)L"[INFO] Mario transition to Attack State \n");
}

void MarioAttackState::Update(float deltaTime)
{
	this->_cooldown -= deltaTime;
	DebugOut((wchar_t*)L"[INFO] Mario Attack cooldown = %f \n", this->_cooldown);
	if (this->_cooldown <= 0)
	{
		this->_context->direction = this->_context->direction == Direction::LEFT ? Direction::RIGHT : Direction::LEFT;
		this->_cooldown = ATTACK_COOLDOWN;
		KeyboardHandler* keyboard = KeyboardHandler::GetInstance();
		if (this->_context->acceleration.y != 0) // fall
		{
			this->_context->TransitionTo(new MarioFallState());
		}
		else if (keyboard->IsKeyDown(DIK_LEFT))
		{
			this->_context->TransitionTo(new MarioRunState(-1));
		}
		else if (keyboard->IsKeyDown(DIK_RIGHT))
		{
			this->_context->TransitionTo(new MarioRunState(1));
		}
		else
		{
			this->_context->TransitionTo(new MarioIdleState());
		}
	}
}

void MarioAttackState::OnTransition()
{
	this->_context->direction = this->_context->direction == Direction::LEFT ? Direction::RIGHT : Direction::LEFT;
	this->_context->velocity = VECTOR2D(0.0f, this->_context->velocity.y);
	this->_context->acceleration = VECTOR2D(0.0f, this->_context->acceleration.y);
}
