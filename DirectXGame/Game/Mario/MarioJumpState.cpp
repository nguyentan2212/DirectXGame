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
    this->_context->velocity = VECTOR2D(this->_context->velocity.x, MARIO_JUMP_SPEED_Y);
    this->_context->acceleration = VECTOR2D(0.0f, -MARIO_GRAVITY);
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
    string st = typeid(*colEvent.collisionObj).name();
    if (st == "class Brick")
    {
        this->_context->position += this->_context->velocity * colEvent.entryTimePercent * colEvent.deltaTime / 1000;
        this->_context->velocity = VECTOR2D(0, 0);
        this->_context->acceleration = VECTOR2D(0.0f, 0.0f);
        this->_context->TransitionTo(new MarioFallState());
    }
}

void MarioJumpState::OnKeyDown(int keyCode)
{
    if ((keyCode == DIK_LEFT && this->_context->velocity.x >= 0)
        || (keyCode == DIK_RIGHT && this->_context->velocity.x <= 0))
    {
        int direction = (keyCode - DIK_LEFT) - 1;
        this->_context->velocity = VECTOR2D(direction * MARIO_RUN_MAX_SPEED_X / 4.0f, this->_context->velocity.y);
    }
}

void MarioJumpState::OnKeyUp(int keyCode)
{
    if (keyCode == DIK_UP)
    {
        this->_context->TransitionTo(new MarioFallState());
    }
}