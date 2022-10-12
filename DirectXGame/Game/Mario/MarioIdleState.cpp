#include "MarioIdleState.h"
#include "../../Graphic/AnimationService.h"
#include "../../Core/GameObject.h"
#include "MarioRunState.h"
#include "MarioJumpState.h"
#include "MarioSitState.h"

MarioIdleState::MarioIdleState()
{
	AnimationService* animations = AnimationService::GetInstance();
	this->_animation = animations->GetAnimation("super mario idle");

	DebugOut((wchar_t*)L"[INFO] Mario transition to Idle State \n");
}

void MarioIdleState::Update(float deltaTime)
{
	this->_animation->Update(deltaTime);
}

Animation* MarioIdleState::GetAnimation()
{
	return this->_animation;
}

void MarioIdleState::Run(float speed)
{
	this->_context->velocity = VECTOR2D(speed, 0);
	this->_context->TransitionTo(new MarioRunState());
}

void MarioIdleState::Jump(float speed)
{
	this->_context->velocity = VECTOR2D(0, speed);
	this->_context->TransitionTo(new MarioJumpState());
}

void MarioIdleState::Sit()
{
	this->_context->TransitionTo(new MarioSitState());
}
