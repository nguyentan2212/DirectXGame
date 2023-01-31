#include "KoopaParaTroopa.h"
#include "../../Graphic/SpriteService.h"
#include "../../Physic/CollisionManager.h"
#include "../../Core/ObjectPool.h"

KoopaParaTroopa::KoopaParaTroopa(): GameObject()
{
	this->_name = "koopa paratroopa";
	this->_width = KOOPA_PARATROOPA_WIDTH;
	this->_height = KOOPA_PARATROOPA_HEIGHT;
	this->_head = new Head(KOOPA_PARATROOPA_WIDTH / 2.0f, KOOPA_PARATROOPA_HEIGHT);
	this->_head->body = this;
	this->_head->SetGravity(KOOPA_PARATROOPA_GRAVITY);
	ObjectPool* pool = ObjectPool::GetInstance();
	pool->AddGameObject(this->_head);
	SetState(KOOPA_PARATROOPA_WALK);
}

void KoopaParaTroopa::Update(float deltaTime)
{
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
	string objName = colEvent.collisionObj->name;
	if (objName == "ground" || objName == "cloud" || objName == "panel")
	{
		if (colEvent.direction == Direction::DOWN)
		{
			this->_isGrounded = true;
			this->_position += this->_velocity * colEvent.entryTime;
			this->_velocity = VECTOR2D(this->_velocity.x, 0);
			this->_acceleration = VECTOR2D(this->_acceleration.x, 0.0f);
		}
		else if (GetState() == KOOPA_PARATROOPA_RUN)
		{
			this->_velocity = VECTOR2D(-this->_velocity.x, this->_velocity.y);
		}
	}
	else if (objName == "mario")
	{
		if (colEvent.direction == Direction::UP && GetState() == KOOPA_PARATROOPA_WALK)
		{
			SetState(KOOPA_PARATROOPA_STUN);
		}
	}
}

void KoopaParaTroopa::SetState(UINT stateValue, string stateName)
{
	switch (stateValue)
	{
	case KOOPA_PARATROOPA_WALK:
		if (GetState() > 0)
		{
			return;
		}
		Walk();
		break;
	case KOOPA_PARATROOPA_RUN:
		if (GetState() != KOOPA_PARATROOPA_STUN)
		{
			return;
		}
		Run();
		break;
	case KOOPA_PARATROOPA_STUN:
		if (GetState() != KOOPA_PARATROOPA_WALK)
		{
			return;
		}
		Stun();
		break;
	default:
		return;
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
	case KOOPA_PARATROOPA_STUN:
		aniName += "stand";
		break;
	default:
		break;
	}
	return anis->GetAnimation(aniName);
}

void KoopaParaTroopa::Walk()
{
	this->velocity = VECTOR2D(KOOPA_PARATROOPA_WALK_SPEED_X, 0.0f);
	this->acceleration = VECTOR2D(0.0f, 0.0f);
	this->_head->isActive = true;
}

void KoopaParaTroopa::Run()
{
	this->velocity = VECTOR2D(KOOPA_PARATROOPA_RUN_SPEED_X * this->_direction, 0.0f);
	this->acceleration = VECTOR2D(0.0f, 0.0f);
	this->_head->isActive = false;
}

void KoopaParaTroopa::Stun()
{
	this->velocity = VECTOR2D(0.0f, 0.0f);
	this->acceleration = VECTOR2D(0.0f, 0.0f);
	this->_height = KOOPA_PARATROOPA_WIDTH;
	VECTOR2D pos = this->_position;
	pos.y -= (KOOPA_PARATROOPA_HEIGHT - KOOPA_PARATROOPA_WIDTH) / 2;
	this->position = pos;
	this->_head->isActive = false;
}
