#include "CollisionEvent.h"
#include "../Core/GameObject.h"

CollisionEvent::CollisionEvent(GameObject* obj, DIRECTION direction, float entryTime)
{
	this->collisionObj = obj;
	this->direction = direction;
	this->entryTime = entryTime;
}

CollisionEvent::~CollisionEvent()
{
	
}

CollisionEvent CollisionEvent::NoCollision()
{
	return CollisionEvent(nullptr, DIRECTION::NONE, 1.0f);
}
