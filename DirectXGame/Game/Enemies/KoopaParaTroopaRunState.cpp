#include "KoopaParaTroopaRunState.h"
#include "../../Core/GameObject.h"
#include "../../Physic/CollisionManager.h"
#include "../Mario/Mario.h"
#include "../Mario/MarioDeathState.h"

KoopaParaTroopaRunState::KoopaParaTroopaRunState(int direction)
{
	this->_name = "run";
	this->_direction = direction;
	this->_isGrounded = true;
	DebugOut((wchar_t*)L"[INFO] Koopa Paratroopa transition to Run State \n");
}

void KoopaParaTroopaRunState::OnTransition()
{
	this->_context->width = 16;
	this->_context->height = 16;
	this->_context->velocity = VECTOR2D(KOOPA_PARATROOPA_RUN_SPEED_X * this->_direction, 0.0f);
	this->_context->acceleration = VECTOR2D(0.0f, 0.0f);
}

void KoopaParaTroopaRunState::Update(float deltaTime)
{
	/*CollisionManager* collision = CollisionManager::GetInstance();
	list<GameObject*> results = collision->RayCastWith(this->_context, DIRECTION::DOWN, 5.0f, deltaTime);
	for (GameObject* obj : results)
	{
		if (obj->name == "ground" || obj->name == "panel")
		{
			this->_isGrounded = true;
		}
	}*/
	if (this->_isGrounded)
	{
		this->_context->acceleration = VECTOR2D(0.0f, 0.0f);
	}
	else
	{
		this->_context->acceleration = VECTOR2D(0.0f, -KOOPA_PARATROOPA_GRAVITY);
	}
	this->_isGrounded = false;
}

void KoopaParaTroopaRunState::OnCollision(CollisionEvent colEvent)
{
	string className = typeid(*colEvent.collisionObj).name();

	if (colEvent.collisionObj->name == "pine" || colEvent.collisionObj->name == "ground" || className == "class Brick")
	{
		if (colEvent.direction == Direction::LEFT || colEvent.direction == Direction::RIGHT)
		{
			VECTOR2D v = this->_context->velocity;
			v.x *= -1;
			this->_context->velocity = v;
		}
		else if (colEvent.direction == Direction::DOWN)
		{
			this->_context->position += this->_context->velocity * colEvent.entryTime;
			VECTOR2D v = this->_context->velocity;
			v.y = 0.0f;
			this->_context->velocity = v;
			VECTOR2D a = this->_context->acceleration;
			a.y = 0.0f;
			this->_context->acceleration = a;
		}
	}
	else
	{
		Mario* mario = dynamic_cast<Mario*>(colEvent.collisionObj);
		if (mario != nullptr && mario->GetStateName() != "kick")
		{
			string stateName = mario->GetStateName();
			if (mario->name != "small mario" && stateName.find("change figure") == string::npos)
			{
				
			}
			else if (stateName.find("change figure") == string::npos && stateName != "death")
			{
				mario->TransitionTo(new MarioDeathState());
			}
		}
	}
}
