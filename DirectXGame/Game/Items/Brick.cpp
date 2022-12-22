#include "Brick.h"

Brick::Brick(): GameObject(new ObjectState())
{
	
}

void Brick::Update(float deltaTime)
{
	GameObject::Update(deltaTime);
	if (this->_isActive == false && this->_y > this->_position.y)
	{
		this->_position.y = this->_y;
		this->_acceleration = VECTOR2D(0.0f, 0.0f);
		this->_velocity = VECTOR2D(0.0f, 0.0f);
	}
}

Animation* Brick::GetAnimation()
{
	AnimationService* animations = AnimationService::GetInstance();
	if (this->_isActive)
	{
		return animations->GetAnimation("brick");
	}
	
	return animations->GetAnimation("brick inactive");
}

void Brick::OnCollision(CollisionEvent colEvent)
{
	if (this->_isActive)
	{
		string st = typeid(*colEvent.collisionObj).name();
		if (st == "class Mario" && colEvent.direction == Direction::DOWN)
		{
			this->_isActive = false;
			this->_y = this->_position.y;
			this->_acceleration = VECTOR2D(this->_acceleration.x, -BRICK_GRAVITY);
			this->_velocity = VECTOR2D(this->_velocity.x, BRICK_BOUND_SPEED);
		}
	}
}
