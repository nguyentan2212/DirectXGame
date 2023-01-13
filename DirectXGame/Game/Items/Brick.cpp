#include "Brick.h"
#include "Coin.h"
#include "Mushroom.h"
#include "Leaf.h"
#include "../../Graphic/SpriteService.h"
#include "../../Graphic/AnimationService.h"
#include "../../Physic/CollisionManager.h"
#include "../../Core/ObjectPool.h"

Brick::Brick(GameObject* content, VECTOR2D position): GameObject()
{
	this->_position = position;
	this->_beginY = position.y;
	this->_isTouched = false;
	this->_name = "brick";
	this->_height = BRICK_SIZE;
	this->_width = BRICK_SIZE;

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
		if (this->_content->name == "mushroom")
		{
			this->_content->isActive = true;
		}
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
		if (this->_content->name == "score coin")
		{
			this->_content->isActive = true;
		}
	}
	/*else if (colEvent.collisionObj->name == "mario" &&this->_isTouched == false &&
		(colEvent.direction == Direction::LEFT || colEvent.direction == Direction::RIGHT)
		&& this->_content->name == "leaf")
	{
		this->_isTouched = true;
		this->_content->isActive = true;
	}*/
}

Brick* Brick::CreateCoinBrick(VECTOR2D position)
{
	return new Brick(Coin::ScoreCoin(position), position);
}

Brick* Brick::CreateMushroomBrick(VECTOR2D position)
{
	Brick* obj = new Brick(new Mushroom(position), position);
	obj->name = "mushroom brick";
	return obj;
}

Brick* Brick::CreateLeafBrick(VECTOR2D position)
{
	Brick* obj = new Brick(new Leaf(position), position);
	obj->name = "leaf brick";
	return obj;
}
