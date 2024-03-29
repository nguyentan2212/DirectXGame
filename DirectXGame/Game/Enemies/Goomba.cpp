#include "Goomba.h"
#include "../../Graphic/SpriteService.h"
#include "../../Graphic/AnimationService.h"
#include "../../Physic/CollisionManager.h"
#include "../../Core/ObjectPool.h"
#include "../../Game/Mario/Mario.h"

Goomba::Goomba(): GameObject()
{
	this->_name = "goomba";
	this->_width = GOOMBA_SIZE;
	this->_height = GOOMBA_SIZE;
	this->_velocity = VECTOR2D(-GOOMBA_SPEED, 0.0f);

	SpriteService* sprites = SpriteService::GetInstance();
	this->_score = new GameObject(sprites->GetSprite("hub-and-font/100"));
	this->_score->velocity = VECTOR2D(0.0f, GOOMBA_SPEED);
	this->_score->isActive = false;
	SetState(GOOMBA_WALK);
}

void Goomba::Update(float deltaTime)
{
	if (this->_isActive == false)
	{
		return;
	}

	if (GetState() == GOOMBA_DEATH_BY_JUMP || GetState() == GOOMBA_DEATH_BY_ATTACK)
	{
		if (this->_deathDuration > 0)
		{
			this->_deathDuration -= deltaTime;
		}
		else
		{
			this->_isActive = false;
			this->_score->isActive = false;
		}
	}
	if (this->_score != nullptr && this->_score->isActive)
	{
		this->_score->Update(deltaTime);
	}
	
	ObjectPool* pool = ObjectPool::GetInstance();
	if (this->_head == nullptr)
	{
		this->_head = new Head(GOOMBA_SIZE * 0.5, GOOMBA_SIZE);
		this->_head->position = this->position + VECTOR2D(this->width / 2.0f, 0.0f);
		this->_head->body = this;
		this->_head->SetGravity(GOOMBA_GRAVITY);
		
		pool->AddGameObject(this->_head);
	}

	GameObject* mario = pool->GetGameObjectWithClass("Mario");
	float distance = abs(this->position.x - mario->position.x);
	if (distance < GOOMBA_REMOVE_HEAD_DISTANCE)
	{
		this->_head->isActive = false;
	}

	this->_acceleration = VECTOR2D(0.0f, -this->_gravity);
	this->_velocity += this->_acceleration * deltaTime / 1000;

	this->_isGrounded = false;
	CollisionManager::Processing(this, deltaTime);
	Translate(this->_velocity * deltaTime / 1000);
}

void Goomba::OnCollision(CollisionEvent colEvent)
{
	if (this->_isBlocking || GetState() == GOOMBA_DEATH_BY_JUMP || GetState() == GOOMBA_DEATH_BY_ATTACK)
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
		else if (objName != "panel" && (colEvent.direction == Direction::LEFT || colEvent.direction == Direction::RIGHT))
		{
			this->_velocity = VECTOR2D(-this->_velocity.x, this->_velocity.y);
		}
	}
	else if (objName == "mario")
	{
		Mario* mario = dynamic_cast<Mario*>(colEvent.collisionObj);
		if (colEvent.direction == Direction::UP)
		{
			SetState(GOOMBA_DEATH_BY_JUMP);
			mario->IncreaseScore(SCORE_GOOMBA_DEATH);
		}
		else if (colEvent.collisionObj->GetState() == MARIO_ATTACK)
		{
			SetState(GOOMBA_DEATH_BY_ATTACK);
			mario->IncreaseScore(SCORE_GOOMBA_DEATH);
		}

	}
}

void Goomba::SetState(UINT stateValue, string stateName)
{
	if (GetState() == GOOMBA_DEATH_BY_JUMP || GetState() == GOOMBA_DEATH_BY_ATTACK)
	{
		return;
	}
	this->_states[stateName] = stateValue;
	switch (stateValue)
	{
	case GOOMBA_WALK:
		break;
	case GOOMBA_DEATH_BY_JUMP:
	case GOOMBA_DEATH_BY_ATTACK:
		Death();
		break;
	default:
		break;
	}
	
}

void Goomba::Render()
{
	GameObject::Render();
	if (this->_score != nullptr && this->_score->isActive)
	{
		this->_score->Render();
	}
}

Renderable* Goomba::GetRenderable()
{
	if (GetState() == GOOMBA_DEATH_BY_JUMP)
	{
		SpriteService* sprites = SpriteService::GetInstance();
		return sprites->GetSprite("enemies/goomba/2");
	}
	if (GetState() == GOOMBA_DEATH_BY_ATTACK)
	{
		SpriteService* sprites = SpriteService::GetInstance();
		return sprites->GetSprite("enemies/goomba/3");
	}

	AnimationService* anis = AnimationService::GetInstance();
	return anis->GetAnimation("goomba walk");
}

void Goomba::Death()
{
	if (GetState() == GOOMBA_DEATH_BY_JUMP)
	{
		this->_velocity = VECTOR2D(0.0f, 0.0f);
		this->_gravity = 0;
		this->_height = GOOMBA_DEATH_HEIGHT;
		this->_position = this->_position - VECTOR2D(0.0f, GOOMBA_SIZE - GOOMBA_DEATH_HEIGHT) / 2.0f;
	}
	else
	{
		this->_velocity = VECTOR2D(0.0f, GOOMBA_JUMP_DEFLECT_SPEED);
		this->_gravity = GOOMBA_GRAVITY;
	}
	this->_score->position = position + VECTOR2D(0.0f, GOOMBA_SIZE);
	this->_score->isActive = true;
}
