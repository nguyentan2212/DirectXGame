#include "MarioFallState.h"
#include "MarioJumpState.h"
#include "MarioIdleState.h"
#include "MarioRunState.h"
#include "MarioAttackState.h"
#include "../../Core/GameObject.h"
#include "../../Core/KeyboardHandler.h"
#include "Mario.h"

MarioFallState::MarioFallState()
{
    this->_name = "fall";
    DebugOut((wchar_t*)L"[INFO] Mario transition to Fall State \n");
}

void MarioFallState::OnTransition()
{
    this->_context->velocity = VECTOR2D(this->_context->velocity.x, 0.0f);
}

void MarioFallState::Update(float deltaTime)
{
}

void MarioFallState::OnCollision(CollisionEvent colEvent)
{
    Mario* mario = dynamic_cast<Mario*>(this->_context);
    if (mario != nullptr && mario->isGrounded)
    {
        KeyboardHandler* keyboard = KeyboardHandler::GetInstance();
        if (keyboard->IsKeyDown(DIK_LEFT)) // prev was running left
        {
            mario->velocity = VECTOR2D(-abs(mario->velocity.x), 0.0f);
            mario->TransitionTo(new MarioRunState(-1));
        }
        else if (keyboard->IsKeyDown(DIK_RIGHT)) // prev was running left
        {
            mario->velocity = VECTOR2D(abs(mario->velocity.x), 0.0f);
            mario->TransitionTo(new MarioRunState(1));
        }
        else
        {
            mario->TransitionTo(new MarioIdleState());
        }
    }
}

void MarioFallState::OnKeyDown(int keyCode)
{
    if ((keyCode == DIK_LEFT && this->_context->velocity.x >= 0)
        || (keyCode == DIK_RIGHT && this->_context->velocity.x <= 0))
    {
        int direction = (keyCode - DIK_LEFT) - 1;
        this->_context->velocity = VECTOR2D(direction * MARIO_RUN_MAX_SPEED_X / 2.0f, this->_context->velocity.y);
    }
    else if (keyCode == DIK_A && this->_context->name == "raccoon mario")
    {
        this->_context->TransitionTo(new MarioAttackState());
    }
}
