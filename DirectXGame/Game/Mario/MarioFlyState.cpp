#include "MarioFlyState.h"
#include "MarioConst.h"
#include "MarioRunState.h"
#include "MarioIdleState.h"
#include <dinput.h>
#include "../../Core/KeyboardHandler.h"

MarioFlyState::MarioFlyState()
{
	this->_name = "fly";
	DebugOut((wchar_t*)L"[INFO] Mario transition to Fly State \n");
}

void MarioFlyState::OnTransition()
{
	this->_context->velocity = VECTOR2D(this->_context->velocity.x, MARIO_JUMP_SPEED_Y / 2.0f);
	this->_context->acceleration = VECTOR2D(this->_context->acceleration.x, 0.0f);
}

void MarioFlyState::Update(float deltaTime)
{
	KeyboardHandler* keyboard = KeyboardHandler::GetInstance();
	if (keyboard->IsKeyDown(DIK_UP) == false)
	{
		this->_context->acceleration = VECTOR2D(this->_context->acceleration.x, -MARIO_GRAVITY);
	}
}

void MarioFlyState::OnCollision(CollisionEvent colEvent)
{
	string n = colEvent.collisionObj->name;
	string typeName = typeid(*colEvent.collisionObj).name();
	if ((n == "ground" || n == "panel" || n == "cloud" || typeName == "class Brick") && colEvent.direction == Direction::DOWN)
	{
		this->_context->position += this->_context->velocity * colEvent.entryTime;
		this->_context->velocity = VECTOR2D(this->_context->velocity.x, 0);

		KeyboardHandler* keyboard = KeyboardHandler::GetInstance();
		if (keyboard->IsKeyDown(DIK_LEFT))
		{
			this->_context->TransitionTo(new MarioRunState(-1));
		}
		else if (keyboard->IsKeyDown(DIK_RIGHT))
		{
			this->_context->TransitionTo(new MarioRunState(1));
		}
		else
		{
			this->_context->TransitionTo(new MarioIdleState());
		}
		
	}
}

void MarioFlyState::OnKeyDown(int keyCode)
{
	if (keyCode == DIK_UP)
	{
		this->_context->velocity = VECTOR2D(this->_context->velocity.x, MARIO_JUMP_SPEED_Y / 2.0f);
		this->_context->acceleration = VECTOR2D(this->_context->acceleration.x, 0.0f);
	}
	else if (keyCode == DIK_LEFT)
	{
		this->_context->velocity = VECTOR2D(-MARIO_RUN_MAX_SPEED_X / 2.0f, this->_context->velocity.y);
		this->_context->acceleration = VECTOR2D(0.0f, 0.0f);
	}
	else if (keyCode == DIK_RIGHT)
	{
		this->_context->velocity = VECTOR2D(MARIO_RUN_MAX_SPEED_X / 2.0f, this->_context->velocity.y);
		this->_context->acceleration = VECTOR2D(0.0f, 0.0f);
	}
}

void MarioFlyState::OnKeyUp(int keyCode)
{
	if (keyCode == DIK_UP)
	{
		this->_context->acceleration = VECTOR2D(this->_context->acceleration.x, -MARIO_GRAVITY);
	}
	else if (keyCode == DIK_RIGHT || keyCode == DIK_LEFT)
	{
		this->_context->velocity = VECTOR2D(0.0f, this->_context->velocity.y);
		this->_context->acceleration = VECTOR2D(0.0f, 0.0f);
	}
}
