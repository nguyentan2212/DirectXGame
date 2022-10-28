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

    this->_width = 16.0f;
    this->_height = 32.0f;
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

void MarioRunState::OnCollision(CollisionEvent colEvent)
{
    if (colEvent.collisionObj->name == "pine")
    {
        this->_context->position += this->_context->velocity * colEvent.entryTimePercent * colEvent.deltaTime / 1000;
        this->_context->velocity = VECTOR2D(0, 0);
    }
}

void MarioRunState::Jump(float speed)
{
    this->_context->velocity += VECTOR2D(0, speed);
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
