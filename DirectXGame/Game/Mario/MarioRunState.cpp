#include "MarioRunState.h"
#include "../../Core/GameObject.h"
#include "../../Graphic/AnimationService.h"

MarioRunState::MarioRunState(): ObjectState()
{
    AnimationService* animations = AnimationService::GetInstance();
    this->_animation = animations->GetAnimation("super mario run");
    
}

void MarioRunState::Update(float deltaTime)
{
    this->_animation->Update(deltaTime);
}

Animation* MarioRunState::GetAnimation()
{
    return this->_animation;
}
