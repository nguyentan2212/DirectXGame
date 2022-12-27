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
    this->_context->velocity = VECTOR2D(this->_context->velocity.x, 0.0f);
    this->_context->acceleration = VECTOR2D(this->_context->acceleration.x, - MARIO_GRAVITY);
}

void MarioFallState::Update(float deltaTime)
{
    if (this->_context->name == "small mario")
    {
        this->_context->width = 16.0f;
        this->_context->height = 16.0f;
    }
    else if (this->_context->name == "super mario")
    {
        this->_context->width = 16.0f;
        this->_context->height = 28.0f;
    }
    else if (this->_context->name == "raccoon mario")
    {
        this->_context->width = 23.0f;
        this->_context->height = 27.0f;
    }
}

void MarioFallState::OnCollision(CollisionEvent colEvent)
{
    string objName = colEvent.collisionObj->name;
    if (colEvent.direction == DIRECTION::DOWN && (objName == "pine" || objName == "ground" || objName == "panel" || objName == "cloud"))
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
            this->_context->TransitionTo(new MarioRunState(1));
        }
        else
        {
            this->_context->TransitionTo(new MarioIdleState());
        }
    }
}
