#include "Mushroom.h"
#include "../../Graphic/SpriteService.h"
#include "../../Physic/CollisionManager.h"
#include "../../Core/ObjectPool.h"

Mushroom::Mushroom(VECTOR2D position): GameObject()
{
	this->position = position;
	this->_beginY = position.y;
	this->_height = MUSHROOM_SIZE;
	this->_width = MUSHROOM_SIZE;
	this->_velocity = VECTOR2D(0.0f, MUSHROOM_Y_SPEED);
	this->_isReady = false;
	this->_name = "mushroom";
	
	ObjectPool* pool = ObjectPool::GetInstance();
	SpriteService* sprites = SpriteService::GetInstance();
	this->_score = new GameObject(sprites->GetSprite("hub-and-font/100"));
	this->_score->velocity = VECTOR2D(0.0f, MUSHROOM_SCORE_SPEED);
	this->_score->isActive = false;
	pool->AddGameObject(this->_score);
}

void Mushroom::Update(float deltaTime)
{
	if (this->_isActive == false)
	{
		return;
	}

	// update score
	if (this->_score != nullptr)
	{
		this->_score->Update(deltaTime);
	}

	if (this->_score != nullptr && this->_score->isActive 
		&& this->_score->position.y > this->_position.y + MUSHROOM_SCORE_MAX_LENGHT)
	{
		this->_score->isActive = false;
		this->isActive = false;
	}

	// mushroom update
	if (this->_isReady == false && this->_acceleration.y == 0 && this->_position.y >= this->_beginY + MUSHROOM_SIZE)
	{
		this->_acceleration = VECTOR2D(0.0f, -MUSHROOM_GRAVITY);
		this->_velocity = VECTOR2D(MUSHROOM_X_SPEED, this->_velocity.y);
		this->_isReady = true;
	}
	else if (this->_isReady)
	{
		this->_acceleration = VECTOR2D(0.0f, -MUSHROOM_GRAVITY);
	}
	else
	{
		this->_acceleration = VECTOR2D(0.0f, 0.0f);
	}

	// main update
	this->_velocity += this->_acceleration * deltaTime / 1000;
	IsBlocking();
	this->_isGrounded = false;
	CollisionManager::Processing(this, deltaTime);
	Translate(this->_velocity * deltaTime / 1000);
}

void Mushroom::OnCollision(CollisionEvent colEvent)
{
	string objName = colEvent.collisionObj->name;
	if (objName == "pine" || objName == "ground" || objName == "panel" || objName == "brick")
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
		this->_score->isActive = true;
		this->isBlocking = true;
		this->_score->position = position + VECTOR2D(0.0f, MUSHROOM_SIZE);
	}
}

void Mushroom::Render()
{
	GameObject::Render(0.1f);
}

Renderable* Mushroom::GetRenderable()
{
	if (this->_score->isActive)
	{
		return nullptr;
	}

	SpriteService* sprites = SpriteService::GetInstance();
	return sprites->GetSprite("mics107");
}
