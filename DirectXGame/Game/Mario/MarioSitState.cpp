#include "MarioSitState.h"
#include "../../Graphic/AnimationService.h"
#include "../../Core/GameObject.h"
#include "MarioIdleState.h"

MarioSitState::MarioSitState(): ObjectState()
{
	AnimationService* animations = AnimationService::GetInstance();
	this->_animation = animations->GetAnimation("super mario sit");

	this->_width = 16.0f;
	this->_height = 24.0f;
	DebugOut((wchar_t*)L"[INFO] Mario transition to Sit State \n");
}

void MarioSitState::Update(float deltaTime)
{
	this->_animation->Update(deltaTime);
}

Animation* MarioSitState::GetAnimation()
{
	return this->_animation;
}

void MarioSitState::Idle()
{
	this->_context->TransitionTo(new MarioIdleState());
}
