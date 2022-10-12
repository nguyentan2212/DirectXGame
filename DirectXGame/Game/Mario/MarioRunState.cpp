#include "MarioRunState.h"
#include "../../Graphic/AnimationService.h"
#include "../../Core/GameObject.h"
#include "MarioJumpState.h"
#include "MarioIdleState.h"
#include "MarioSitState.h"

MarioRunState::MarioRunState(): ObjectState()
{
    AnimationService* animations = AnimationService::GetInstance();
    this->_animation = animations->GetAnimation("super mario run");

    DebugOut((wchar_t*)L"[INFO] Mario transition to Run State \n");
}

void MarioRunState::Update(float deltaTime)
{
    this->_animation->Update(deltaTime);
}

Animation* MarioRunState::GetAnimation()
{
    return this->_animation;
}

void MarioRunState::Jump(float speed)
{
    this->_context->velocity += VECTOR2D(speed, 0);
    this->_context->TransitionTo(new MarioJumpState());
}

void MarioRunState::Idle()
{
    this->_context->velocity = VECTOR2D(0, 0);
    this->_context->TransitionTo(new MarioIdleState());
}

void MarioRunState::Sit()
{
    this->_context->velocity = VECTOR2D(0.0f, 0.0f);
    this->_context->TransitionTo(new MarioSitState());
}
