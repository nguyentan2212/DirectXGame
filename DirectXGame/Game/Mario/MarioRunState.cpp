#include "MarioRunState.h"
#include "../../Graphic/AnimationService.h"
#include "../../Core/GameObject.h"
#include "MarioJumpState.h"
#include "MarioIdleState.h"
#include "MarioSitState.h"
#include <dinput.h>

MarioRunState::MarioRunState(): ObjectState()
{
    AnimationService* animations = AnimationService::GetInstance();
    //this->_animation = animations->GetAnimation("super mario run");

    this->_width = 16.0f;
    this->_height = 32.0f;
	this->_name = "run";
    DebugOut((wchar_t*)L"[INFO] Mario transition to Run State \n");
}

void MarioRunState::OnCollision(CollisionEvent colEvent)
{
    if (colEvent.collisionObj->name == "pine")
    {
        this->_context->position += this->_context->velocity * colEvent.entryTimePercent * colEvent.deltaTime / 1000;
        this->_context->velocity = VECTOR2D(0, 0);
    }
}

void MarioRunState::OnKeyDown(int keyCode)
{
	if (keyCode == DIK_UP)
	{
		this->_context->velocity = VECTOR2D(0.0f, 100);
		this->_context->TransitionTo(new MarioJumpState());
	}
	else if (keyCode == DIK_DOWN)
	{
		this->_context->velocity = VECTOR2D(0.0f, 0.0f);
		this->_context->TransitionTo(new MarioSitState());
	}
}

void MarioRunState::OnKeyUp(int keyCode)
{
	if (keyCode == DIK_LEFT || keyCode == DIK_RIGHT)
	{
		this->_context->velocity = VECTOR2D(0.0f, 0.0f);
		this->_context->TransitionTo(new MarioIdleState());
	}
}
