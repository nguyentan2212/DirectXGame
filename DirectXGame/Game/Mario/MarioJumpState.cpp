#include "MarioJumpState.h"
#include "../../Core/GameObject.h"
#include "MarioRunState.h"
#include "MarioIdleState.h"
#include "MarioFallState.h"
#include "Mario.h"
#include <dinput.h>

MarioJumpState::MarioJumpState()
{
    this->_name = "jump";
    DebugOut((wchar_t*)L"[INFO] Mario transition to Jump State \n");
}

void MarioJumpState::OnTransition()
{
    if (this->_context->name == "small mario")
    {
        this->_width = 12.0f;
        this->_height = 16.0f;
    }
    else
    {
        this->_width = 16.0f;
        this->_height = 32.0f;
    }
    this->_context->velocity = VECTOR2D(this->_context->velocity.x, MARIO_JUMP_SPEED_Y);
    this->_context->acceleration = VECTOR2D(this->_context->acceleration.x, -MARIO_GRAVITY);
}

void MarioJumpState::Update(float deltaTime)
{
    if (this->_context->velocity.y < 0)// fall
    {
        this->_context->TransitionTo(new MarioFallState());
    }
}

void MarioJumpState::OnCollision(CollisionEvent colEvent)
{
    
}

void MarioJumpState::OnKeyDown(int keyCode)
{
}

void MarioJumpState::OnKeyUp(int keyCode)
{
    if (keyCode == DIK_UP)
    {
        this->_context->TransitionTo(new MarioFallState());
    }
}
