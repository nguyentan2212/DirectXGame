#include "MarioSitState.h"
#include "../../Graphic/AnimationService.h"

MarioSitState::MarioSitState(): ObjectState()
{
	AnimationService* animations = AnimationService::GetInstance();
	this->_animation = animations->GetAnimation("super mario sit");
}

void MarioSitState::Update(float deltaTime)
{
	this->_animation->Update(deltaTime);
}

Animation* MarioSitState::GetAnimation()
{
	return this->_animation;
}
