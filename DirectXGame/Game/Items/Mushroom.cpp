#include "Mushroom.h"
#include "../../Graphic/SpriteService.h"
#include "../../Physic/CollisionManager.h"

Mushroom::Mushroom(VECTOR2D position): GameObject(new ObjectState())
{
	this->position = position;
	this->_beginY = position.y;
	this->_height = MUSHROOM_SIZE;
	this->_width = MUSHROOM_SIZE;
	this->_velocity = VECTOR2D(0.0f, MUSHROOM_Y_SPEED);
	this->_isReady = false;
	this->_name = "mushroom";
}

void Mushroom::Update(float deltaTime)
{
	if (this->_isActive == false)
	{
		return;
	}

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

	this->_velocity += this->_acceleration * deltaTime / 1000;
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
			this->_isGrounded = true;
			this->_position += this->_velocity * colEvent.entryTime;
			this->_velocity = VECTOR2D(this->_velocity.x, 0);
			this->_acceleration = VECTOR2D(0.0f, 0.0f);
		}
		else if (objName != "panel" && (colEvent.direction == Direction::LEFT || colEvent.direction == Direction::RIGHT))
		{
			this->_velocity = VECTOR2D(-this->_velocity.x, this->_velocity.y);
		}
	}
}

void Mushroom::Render()
{
	GameObject::Render(0.1f);
}

Renderable* Mushroom::GetRenderable()
{
	SpriteService* sprites = SpriteService::GetInstance();
	return sprites->GetSprite("mics107");
}
