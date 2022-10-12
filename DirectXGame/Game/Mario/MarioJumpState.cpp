#include "MarioJumpState.h"
#include "../../Graphic/AnimationService.h"
#include "../../Core/GameObject.h"
#include "MarioRunState.h"
#include "MarioIdleState.h"

MarioJumpState::MarioJumpState()
{
    AnimationService* animations = AnimationService::GetInstance();
    this->_animation = animations->GetAnimation("super mario jump");

    DebugOut((wchar_t*)L"[INFO] Mario transition to Jump State \n");
}

void MarioJumpState::Update(float deltaTime)
{
    this->_animation->Update(deltaTime);
}

Animation* MarioJumpState::GetAnimation()
{
    return this->_animation;
}

void MarioJumpState::Run(float speed)
{
    VECTOR2D v = this->_context->velocity;
    v.x = speed;
    this->_context->velocity = v;
}

void MarioJumpState::Idle()
{
    this->_context->velocity = VECTOR2D(0.0f, 0.0f);
    this->_context->TransitionTo(new MarioIdleState());
}
