#include "MarioJumpState.h"
#include "../../Graphic/AnimationService.h"
#include "../../Core/GameObject.h"
#include "MarioRunState.h"
#include "MarioIdleState.h"

MarioJumpState::MarioJumpState()
{
    AnimationService* animations = AnimationService::GetInstance();
    this->_animation = animations->GetAnimation("super mario jump");

    this->_width = 16.0f;
    this->_height = 32.0f;
    DebugOut((wchar_t*)L"[INFO] Mario transition to Jump State \n");
}

void MarioJumpState::Update(float deltaTime)
{
    this->_animation->Update(deltaTime);
    VECTOR2D v = this->_context->velocity;
    v.y += GRAVITY * deltaTime / 1000.0f;
    this->_context->velocity = v;
}

Animation* MarioJumpState::GetAnimation()
{
    return this->_animation;
}

void MarioJumpState::OnCollision(CollisionEvent colEvent)
{
    if (colEvent.direction == DIRECTION::DOWN)
    {
        this->_context->position += this->_context->velocity * colEvent.entryTimePercent * colEvent.deltaTime / 1000;
        this->_context->velocity = VECTOR2D(0.0f, 0.0f);
        this->_context->TransitionTo(new MarioIdleState());
    }
}

void MarioJumpState::Run(float speed)
{
    VECTOR2D v = this->_context->velocity;
    v.x = speed;
    this->_context->velocity = v;
}
