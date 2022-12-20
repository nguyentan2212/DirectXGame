#include "MarioFallState.h"
#include "MarioJumpState.h"
#include "MarioIdleState.h"
#include "MarioRunState.h"
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
    if (this->_context->name == "small mario")
    {
        this->_width = 16.0f;
        this->_height = 16.0f;
    }
    else
    {
        this->_width = 16.0f;
        this->_height = 32.0f;
    }
    this->_context->velocity = VECTOR2D(this->_context->velocity.x, 0.0f);
    this->_context->acceleration = VECTOR2D(this->_context->acceleration.x, - MARIO_GRAVITY);
}

void MarioFallState::Update(float deltaTime)
{
}

void MarioFallState::OnCollision(CollisionEvent colEvent)
{
    string objName = colEvent.collisionObj->name;
    if (colEvent.direction == DIRECTION::DOWN && objName == "pine" || objName == "ground" || objName == "panel")
    {
        KeyboardHandler* keyboard = KeyboardHandler::GetInstance();
        if (keyboard->IsKeyDown(DIK_LEFT)) // prev was running left
        {
            this->_context->velocity = VECTOR2D(-abs(this->_context->velocity.x), 0.0f);
            this->_context->TransitionTo(new MarioRunState(-1));
        }
        else if(keyboard->IsKeyDown(DIK_RIGHT)) // prev was running left
        {
            this->_context->velocity = VECTOR2D(abs(this->_context->velocity.x), 0.0f);
            this->_context->TransitionTo(new MarioRunState(-1));
        }
        else
        {
            this->_context->TransitionTo(new MarioIdleState());
        }
    }
}
