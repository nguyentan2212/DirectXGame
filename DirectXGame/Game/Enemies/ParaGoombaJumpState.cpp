#include "ParaGoombaJumpState.h"
#include "../../Core/GameObject.h"
#include "ParaGoombaNormalState.h"

ParaGoombaJumpState::ParaGoombaJumpState()
{
	this->_name = "jump";
	DebugOut((wchar_t*)L"[INFO] Para Goomba transition to Jump State \n");
}

void ParaGoombaJumpState::Update(float deltaTime)
{
	this->_cooldown -= deltaTime;
	if (this->_cooldown <= 0 && this->_context->velocity.y == 0.0f && this->_jumptCount == PARAGOOMBA_JUMP_COUNT)
	{
		this->_cooldown = PARAGOOMBA_JUMP_COOLDOWN;

		int direction = this->_context->velocity.x < 0 ? -1 : 1;
		this->_context->TransitionTo(new ParaGoombaNormalState(direction));
	}
}

void ParaGoombaJumpState::OnTransition()
{
	this->_context->width = 16;
	this->_context->height = 16;
	this->_context->velocity = VECTOR2D(this->_context->velocity.x, PARAGOOMBA_SPEED_Y / 2.0f);
	this->_context->acceleration = VECTOR2D(0.0f, -PARAGOOMBA_GRAVITY);
}

void ParaGoombaJumpState::OnCollision(CollisionEvent colEvent)
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
			this->_jumptCount++;
			if (this->_jumptCount < PARAGOOMBA_JUMP_COUNT - 1)
			{
				this->_context->velocity = VECTOR2D(this->_context->velocity.x, PARAGOOMBA_SPEED_Y / 2.0f);
			}
			else if (this->_jumptCount == PARAGOOMBA_JUMP_COUNT - 1)
			{
				this->_context->velocity = VECTOR2D(this->_context->velocity.x, PARAGOOMBA_SPEED_Y);
			}
			else
			{
				this->_context->velocity = VECTOR2D(this->_context->velocity.x, 0.0f);
				this->_context->acceleration = VECTOR2D(0.0f, 0.0f);
			}
			
		}
		else if (colEvent.direction == Direction::UP)
		{
			this->_context->position += this->_context->velocity * colEvent.entryTimePercent * colEvent.deltaTime / 1000;
			this->_context->velocity = VECTOR2D(this->_context->velocity.x, 0.0f);
		}
	}
}
