#include "ParaGoombaNormalState.h"
#include "../../Core/GameObject.h"
#include "ParaGoombaJumpState.h"
#include "ParaGoomba.h"

ParaGoombaNormalState::ParaGoombaNormalState(int direction)
{
	this->_name = "normal";
	this->_direction = direction;
	DebugOut((wchar_t*)L"[INFO] Para Goomba transition to Normal State \n");
}

void ParaGoombaNormalState::Update(float deltaTime)
{
	this->_cooldown -= deltaTime;
	ParaGoomba* paragoomba = dynamic_cast<ParaGoomba*>(this->_context);

	if (this->_cooldown <= 0 && !paragoomba->isLostWings && !paragoomba->isDeath)
	{
		this->_cooldown = PARAGOOMBA_WALK_COOLDOWN;
		this->_context->TransitionTo(new ParaGoombaJumpState());
	}
}

void ParaGoombaNormalState::OnTransition()
{
	this->_context->width = 16;
	this->_context->height = 16;
	this->_context->velocity = VECTOR2D(PARAGOOMBA_SPEED_X * this->_direction, 0.0f);
	this->_context->acceleration = VECTOR2D(0.0f, 0.0f);
}

void ParaGoombaNormalState::OnCollision(CollisionEvent colEvent)
{
	string className = typeid(*colEvent.collisionObj).name();

	if (colEvent.collisionObj->name == "ground" || colEvent.collisionObj->name == "pine" ||
		colEvent.collisionObj->name == "border" || className == "class Brick")
	{
		if (colEvent.direction == Direction::LEFT || colEvent.direction == Direction::RIGHT)
		{
			this->_context->velocity = VECTOR2D(-this->_context->velocity.x, this->_context->velocity.y);
		}
		else if (colEvent.direction == Direction::DOWN)
		{
			this->_context->velocity = VECTOR2D(this->_context->velocity.x, 0.0f);
		}
	}
}
