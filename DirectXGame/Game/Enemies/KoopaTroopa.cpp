#include "KoopaTroopa.h"
#include "../../Graphic/AnimationService.h"
#include "../../Graphic/SpriteService.h"
#include "../../Physic/CollisionManager.h"
#include "../../Core/ObjectPool.h"

KoopaTroopa::KoopaTroopa(bool hasWing) : GameObject()
{
	this->_width = KOOPA_TROOPA_WIDTH;
	this->_height = KOOPA_TROOPA_HEIGHT;
	this->_velocity = VECTOR2D(KOOPA_TROOPA_WALK_SPEED_X, 0.0f);
	SetState(KOOPA_TROOPA_WALK);
	SetState(hasWing ? KOOPA_TROOPA_HAS_WING : KOOPA_TROOPA_LOST_WING, "wing");

	AnimationService* anis = AnimationService::GetInstance();
	this->_wing = new GameObject(anis->GetAnimation("wing"));
}

void KoopaTroopa::Update(float deltaTime)
{
	if (this->_head == nullptr)
	{
		this->_head = new Head(KOOPA_TROOPA_WIDTH * 0.5, KOOPA_TROOPA_HEIGHT);
		this->_head->position = this->position + VECTOR2D(this->width / 2.0f, 0.0f);
		this->_head->body = this;
		this->_head->SetGravity(KOOPA_TROOPA_GRAVITY);
		ObjectPool* pool = ObjectPool::GetInstance();
		pool->AddGameObject(this->_head);
	}

	if (GetState("wing") == KOOPA_TROOPA_HAS_WING)
	{
		if (this->velocity.x < 0 || (this->velocity.x == 0 && this->direction == DIRECTION::LEFT))
		{
			this->_wing->position = this->position + VECTOR2D(this->width / 3.0f, this->height / 3.0f);
		}
		else
		{
			this->_wing->position = this->position + VECTOR2D(-this->width / 3.0f, this->height / 3.0f);
		}
		this->_wing->Update(deltaTime);

		if (this->_runDuration > 0)
		{
			this->_runDuration -= deltaTime;
		}
		else if (this->_isGrounded)
		{
			this->_runDuration = KOOPA_TROOPA_RUN_DURATION;
			Jump();
		}
	}

	if (GetState("wing") == KOOPA_TROOPA_LOST_WING)
	{
		ObjectPool* pool = ObjectPool::GetInstance();
		GameObject* mario = pool->GetGameObjectWithClass("Mario");
		float distance = abs(this->position.x - mario->position.x);
		if (distance < KOOPA_TROOPA_REMOVE_HEAD_DISTANCE)
		{
			this->_head->isActive = false;
		}
	}
	this->_acceleration = VECTOR2D(0.0f, -KOOPA_TROOPA_GRAVITY);
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
}

void KoopaTroopa::Render()
{
	if (this->_isActive == false)
	{
		return;
	}
	_isFlipped = this->_direction == DIRECTION::LEFT ? false : true;
	if (GetState("wing") == KOOPA_TROOPA_HAS_WING)
	{
		this->_wing->isFlipped = this->_isFlipped;
		this->_wing->Render();
	}
	if (this->_score != nullptr)
	{
		this->_score->Render();
	}
	GameObject::Render();
}

void KoopaTroopa::OnCollision(CollisionEvent colEvent)
{
	string objName = colEvent.collisionObj->name;
	string className = typeid(*colEvent.collisionObj).name();

	if (className == "class Platform")
	{
		if (colEvent.direction == Direction::DOWN)
		{
			Grounding(colEvent.entryTime);
			if (GetState() == KOOPA_TROOPA_JUMP)
			{
				ToggleHead();
				SetState(KOOPA_TROOPA_WALK);
			}
		}
	}
	else if (className == "class Brick")
	{
		if (colEvent.direction == DIRECTION::UP)
		{
			VECTOR2D pos = this->position;
			pos.y = this->velocity.y * colEvent.entryTime;
			this->_velocity = VECTOR2D(this->_velocity.x, 0.0f);
			this->_acceleration = VECTOR2D(this->_acceleration.x, -KOOPA_TROOPA_GRAVITY);
		}
		else
		{
			this->_velocity = VECTOR2D(-this->_velocity.x, this->_velocity.y);
		}
		
	}
}

void KoopaTroopa::SetState(UINT stateValue, string stateName)
{
	this->_states[stateName] = stateValue;
}

Renderable* KoopaTroopa::GetRenderable()
{
	AnimationService* anis = AnimationService::GetInstance();
	SpriteService* sprites = SpriteService::GetInstance();
	string aniName = "koopa troopa ";

	switch (GetState())
	{
	case KOOPA_TROOPA_JUMP:
	case KOOPA_TROOPA_WALK:
		aniName += "walk";
		break;
	case KOOPA_TROOPA_RUN:
		aniName += "run";
		break;
	case KOOPA_TROOPA_IS_HELD:
	case KOOPA_TROOPA_STUN:
		return sprites->GetSprite("enemies/koopa-troopa/2");
		break;
	default:
		break;
	}
	return anis->GetAnimation(aniName);
}

void KoopaTroopa::Jump(float speed)
{
}

void KoopaTroopa::ToggleHead()
{
	if (this->_head->isActive == true)
	{
		this->_head->isActive = false;
		return;
	}

	this->_head->isActive = true;
	if (this->velocity.x < 0 || (this->velocity.x == 0 && this->direction == DIRECTION::LEFT))
	{
		this->_head->position = this->position - VECTOR2D(this->width / 2.0f, 0.0f);
	}
	else
	{
		this->_head->position = this->position + VECTOR2D(this->width / 2.0f, 0.0f);
	}
}

void KoopaTroopa::Jump()
{
	if (GetState("wing") != KOOPA_TROOPA_HAS_WING)
	{
		return;
	}
	ToggleHead();
	SetState(KOOPA_TROOPA_JUMP);
	VECTOR2D vec = this->velocity;
	vec.y = KOOPA_TROOPA_JUMP_SPEED;
	this->velocity = vec;
	this->acceleration = VECTOR2D(0.0f, 0.0f);
}
