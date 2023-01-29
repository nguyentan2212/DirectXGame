#include "Head.h"
#include "../../Graphic/SpriteService.h"
#include "../../Physic/CollisionManager.h"

Head::Head(float width, float height): GameObject()
{
	this->_width = width;
	this->_height = height;
	this->_name = "head";
}

void Head::Update(float deltaTime)
{
	this->_acceleration = VECTOR2D(0.0f, -this->_gravity);
	this->_velocity += this->_acceleration * deltaTime / 1000;
	this->_isGrounded = false;
	CollisionManager::Processing(this, deltaTime);
	
	if (this->_isGrounded == false)
	{
		VECTOR2D v = this->body->velocity;
		v.x *= -1.0f;
		this->body->velocity = v;
	}
	
	if (this->body->velocity.x > 0)
	{
		this->position = this->body->position + VECTOR2D(this->body->width / 2.0f, 0.0f);
	}
	else
	{
		this->position = this->body->position - VECTOR2D(this->body->width / 2.0f, 0.0f);
	}
}

void Head::OnCollision(CollisionEvent colEvent)
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
	}
}

void Head::Render()
{
	GameObject::Render();
}

void Head::SetGravity(float gravity)
{
	this->_gravity = gravity;
}
