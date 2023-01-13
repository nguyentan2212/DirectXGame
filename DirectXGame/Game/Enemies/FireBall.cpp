#include "FireBall.h"
#include "../../Physic/CollisionManager.h"

FireBall::FireBall(VECTOR2D begin, float maxLength): GameObject()
{
	this->_begin = begin;
	this->_maxLength = maxLength;
	this->_width = FIREBALL_SIZE;
	this->_height = FIREBALL_SIZE;
	this->_name = "fire ball";
	this->_position = begin;
}

void FireBall::Update(float deltaTime)
{
	if (this->_isActive == false)
	{
		return;
	}
	VECTOR2D temp = GetWorldPosition() - this->_begin;
	float length = D3DXVec2Length(&temp);
	if (length > this->_maxLength)
	{
		this->_isActive = false;
		this->_velocity = VECTOR2D(0.0f, 0.0f);
	}
	
	CollisionManager::Processing(this, deltaTime);
	GameObject::Update(deltaTime);
}

void FireBall::Render()
{
	GameObject::Render(-0.1f);
}

void FireBall::OnCollision(CollisionEvent colEvent)
{
	GameObject* obj = colEvent.collisionObj;

	if (obj->name == "mario")
	{
		this->_isActive = false;
		this->_velocity = VECTOR2D(0.0f, 0.0f);
	}
}

Renderable* FireBall::GetRenderable()
{
	AnimationService* animations = AnimationService::GetInstance();
	return animations->GetAnimation("fire ball");
}

