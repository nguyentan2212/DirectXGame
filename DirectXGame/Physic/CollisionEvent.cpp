#include "CollisionEvent.h"
#include "../Core/GameObject.h"

CollisionEvent::CollisionEvent(GameObject* obj, DIRECTION direction, float entryTimePercent, float deltatime)
{
	this->collisionObj = obj;
	this->direction = direction;
	this->entryTimePercent = entryTimePercent;
	this->deltaTime = deltaTime;
}

CollisionEvent::~CollisionEvent()
{
	
}

CollisionEvent CollisionEvent::NoCollision()
{
	return CollisionEvent(nullptr, DIRECTION::NONE, 1.0f, 0.0f);
}
