#include "Brick.h"
#include "../../Graphic/SpriteService.h"
#include "../../Graphic/AnimationService.h"
#include "../../Physic/CollisionManager.h"
#include "../../Core/ObjectPool.h"

Brick::Brick(GameObject* content, VECTOR2D position): GameObject(new ObjectState())
{
	this->_position = position;
	this->_beginY = position.y;
	this->_isTouched = false;
	this->_name = "brick";

	ObjectPool* pool = ObjectPool::GetInstance();
	this->_content = content;
	this->_content->isActive = false;
	pool->AddGameObject(this->_content);
}

void Brick::Update(float deltaTime)
{
	if (this->_isActive == false)
	{
		return;
	}

	this->_content->Update(deltaTime);
	CollisionManager::Processing(this, deltaTime);
	GameObject::Update(deltaTime);
	if (this->_position.y < this->_beginY && this->_isTouched)
	{
		this->_position = VECTOR2D(this->_position.x, this->_beginY);
		this->_velocity = VECTOR2D(0.0f, 0.0f);
		this->_acceleration = VECTOR2D(0.0f, 0.0f);
	}
}

Renderable* Brick::GetRenderable()
{
	if (this->_isTouched)
	{
		SpriteService* sprites = SpriteService::GetInstance();
		return sprites->GetSprite("mics52");
	}

	AnimationService* animations = AnimationService::GetInstance();
	return animations->GetAnimation("brick");
}

void Brick::OnCollision(CollisionEvent colEvent)
{
	if (colEvent.collisionObj->name == "mario" && colEvent.direction == Direction::DOWN && this->_isTouched == false)
	{
		this->_velocity = VECTOR2D(0.0f, BRICK_BOUND_SPEED);
		this->_acceleration = VECTOR2D(0.0f, -BRICK_GRAVITY);
		this->_isTouched = true;
		this->_content->isActive = true;
	}
}
