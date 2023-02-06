#include "KoopaParaTroopa.h"
#include "../../Graphic/SpriteService.h"
#include "../../Physic/CollisionManager.h"
#include "../../Core/ObjectPool.h"
#include "../Mario/MarioConst.h"

KoopaParaTroopa::KoopaParaTroopa(): GameObject()
{
	this->_width = KOOPA_PARATROOPA_WIDTH;
	this->_height = KOOPA_PARATROOPA_HEIGHT;
	SetState(KOOPA_PARATROOPA_WALK);
}

void KoopaParaTroopa::Update(float deltaTime)
{
	if (GetState() == KOOPA_PARATROOPA_IS_HELD)
	{
		return;
	}

	if (this->_head == nullptr)
	{
		this->_head = new Head(KOOPA_PARATROOPA_WIDTH * 0.5, KOOPA_PARATROOPA_HEIGHT);
		this->_head->position = this->position + VECTOR2D(this->width / 2.0f, 0.0f);
		this->_head->body = this;
		this->_head->SetGravity(KOOPA_PARATROOPA_GRAVITY);
		ObjectPool* pool = ObjectPool::GetInstance();
		pool->AddGameObject(this->_head);
	}
	this->_acceleration = VECTOR2D(0.0f, -KOOPA_PARATROOPA_GRAVITY);
	this->_velocity += this->_acceleration * deltaTime / 1000;

	this->_isGrounded = false;
	CollisionManager::Processing(this, deltaTime);
	
	GameObject::Update(deltaTime);
	if (this->_velocity.x < 0)
	{
		this->_direction = DIRECTION::LEFT;
	}
	else if (this->_velocity.x > 0)
	{
		this->_direction = DIRECTION::RIGHT;
	}
	//DebugOut((wchar_t*)L"[INFO] Koopa x: %f \n", this->_position.x);
}

void KoopaParaTroopa::Render()
{
	_isFlipped = this->_direction == DIRECTION::LEFT ? false : true;
	GameObject::Render();
}

void KoopaParaTroopa::OnCollision(CollisionEvent colEvent)
{
	if (GetState() == KOOPA_PARATROOPA_IS_HELD)
	{
		return;
	}
	string objName = colEvent.collisionObj->name;
	string className = typeid(*colEvent.collisionObj).name();

	if (className == "class Platform" || className == "class Brick")
	{
		if (colEvent.direction == Direction::DOWN)
		{
			Grounding(colEvent.entryTime);
		}
		else if (GetState() == KOOPA_PARATROOPA_RUN && objName != "panel")
		{
			this->_velocity = VECTOR2D(-this->_velocity.x, this->_velocity.y);
		}
	}
}

void KoopaParaTroopa::SetState(UINT stateValue, string stateName)
{
	switch (stateValue)
	{
	case KOOPA_PARATROOPA_WALK:
		this->velocity = VECTOR2D(KOOPA_PARATROOPA_WALK_SPEED_X, 0.0f);
		this->acceleration = VECTOR2D(0.0f, 0.0f);
		if (this->_head != nullptr)
		{
			this->_head->isActive = true;
		}
		break;
	case KOOPA_PARATROOPA_STUN:
		Stun();
		break;
	case KOOPA_PARATROOPA_RUN:
		if (this->direction == DIRECTION::RIGHT)
		{
			this->velocity = VECTOR2D(KOOPA_PARATROOPA_RUN_SPEED_X, 0.0f);
		}
		else
		{
			this->velocity = VECTOR2D(-KOOPA_PARATROOPA_RUN_SPEED_X, 0.0f);
		}
		break;
	case KOOPA_PARATROOPA_IS_HELD:
		break;
		
	default:
		break;
	}
	this->_states[stateName] = stateValue;
}

Renderable* KoopaParaTroopa::GetRenderable()
{
	AnimationService* anis = AnimationService::GetInstance();
	string aniName = "koopa paratroopa ";

	switch (GetState())
	{
	case KOOPA_PARATROOPA_WALK:
		aniName += "walk";
		break;
	case KOOPA_PARATROOPA_RUN:
		aniName += "run";
		break;
	case KOOPA_PARATROOPA_IS_HELD:
	case KOOPA_PARATROOPA_STUN:
		aniName += "stand";
		break;
	default:
		break;
	}
	return anis->GetAnimation(aniName);
}

void KoopaParaTroopa::Stun()
{
	if (GetState() != KOOPA_PARATROOPA_WALK)
	{
		return;
	}
	this->velocity = VECTOR2D(0.0f, 0.0f);
	this->acceleration = VECTOR2D(0.0f, 0.0f);
	this->_height = KOOPA_PARATROOPA_WIDTH;
	VECTOR2D pos = this->_position;
	pos.y -= (KOOPA_PARATROOPA_HEIGHT - KOOPA_PARATROOPA_WIDTH) / 2;
	this->position = pos;
	if (this->_head != nullptr)
	{
		this->_head->isActive = false;
	}
}