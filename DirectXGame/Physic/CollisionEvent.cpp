#include "CollisionEvent.h"
#include "../Core/GameObject.h"

CollisionEvent::CollisionEvent(GameObject* obj, DIRECTION direction, float entryTime, float deltaTime)
{
	this->collisionObj = obj;
	this->direction = direction;
	this->entryTime = entryTime;
	this->deltaTime = deltaTime;
}

CollisionEvent::~CollisionEvent()
{
	
}

CollisionEvent CollisionEvent::NoCollision()
{
	return CollisionEvent(nullptr, DIRECTION::NONE, 1.0f, 0.0f);
}
