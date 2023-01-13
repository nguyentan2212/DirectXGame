#include "Goomba.h"
#include "../../Graphic/SpriteService.h"
#include "../../Graphic/AnimationService.h"
#include "../../Physic/CollisionManager.h"

Goomba::Goomba(): GameObject()
{
	this->_name = "goomba";
	this->_width = GOOMBA_SIZE;
	this->_height = GOOMBA_SIZE;
	this->_velocity = VECTOR2D(-GOOMBA_SPEED, 0.0f);
}

void Goomba::Update(float deltaTime)
{
	if (this->_isActive == false)
	{
		return;
	}

	Renderable* r = GetRenderable();
	if (r != nullptr)
	{
		r->Update(deltaTime);
	}

	if (this->_isDeath)
	{
		if (this->_deathDuration > 0)
		{
			this->_deathDuration -= deltaTime;
		}
		else
		{
			this->_isActive = false;
		}
	}

	this->_acceleration = VECTOR2D(0.0f, -GOOMBA_GRAVITY);
	this->_velocity += this->_acceleration * deltaTime / 1000;
	GameObject::IsBlocking();

	this->_isGrounded = false;
	CollisionManager::Processing(this, deltaTime);
	Translate(this->_velocity * deltaTime / 1000);
}

void Goomba::OnCollision(CollisionEvent colEvent)
{
	string objName = colEvent.collisionObj->name;
	if (objName == "pine" || objName == "ground" || objName == "cloud" || objName == "brick"
		|| objName == "panel")
	{
		if (colEvent.direction == Direction::DOWN)
		{
			this->_isGrounded = true;
			this->_position += this->_velocity * colEvent.entryTime;
			this->_velocity = VECTOR2D(this->_velocity.x, 0);
			this->_acceleration = VECTOR2D(this->_acceleration.x, 0.0f);
		}
		else if (objName != "panel" && (colEvent.direction == Direction::LEFT || colEvent.direction == Direction::RIGHT))
		{
			this->_velocity = VECTOR2D(-this->_velocity.x, this->_velocity.y);
		}
	}
	else if (objName == "mario" && colEvent.direction == Direction::UP && this->_isDeath == false)
	{
		this->_velocity = VECTOR2D(0.0f, 0.0f);
		this->_acceleration = VECTOR2D(0.0f, 0.0f);
		this->_isDeath = true;
		this->_height = GOOMBA_DEATH_HEIGHT;
		this->_position = this->_position - VECTOR2D(0.0f, GOOMBA_SIZE - GOOMBA_DEATH_HEIGHT) / 2.0f;
	}
}

Renderable* Goomba::GetRenderable()
{
	if (this->_isDeath)
	{
		SpriteService* sprites = SpriteService::GetInstance();
		return sprites->GetSprite("enemies/goomba/2");
	}

	AnimationService* anis = AnimationService::GetInstance();
	return anis->GetAnimation("goomba walk");
}