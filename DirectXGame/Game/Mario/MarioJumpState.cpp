#include "MarioJumpState.h"
#include "../../Core/GameObject.h"
#include "MarioRunState.h"
#include "MarioIdleState.h"
#include <dinput.h>

MarioJumpState::MarioJumpState()
{
    this->_width = 16.0f;
    this->_height = 32.0f;
    this->_name = "jump";
    DebugOut((wchar_t*)L"[INFO] Mario transition to Jump State \n");
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

void MarioJumpState::OnKeyDown(int keyCode)
{
}

void MarioJumpState::OnKeyUp(int keyCode)
{
    if (keyCode == DIK_UP)
    {
        this->_context->velocity = VECTOR2D(0.0f, -100.0f);
    }
}
