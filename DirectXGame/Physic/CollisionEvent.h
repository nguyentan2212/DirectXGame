#pragma once
#include "../Utils/CMath.h"

class GameObject;
class CollisionEvent
{
public:
	CollisionEvent(GameObject* obj, DIRECTION direction, float entryTime);
	~CollisionEvent();

	static CollisionEvent NoCollision();

	GameObject* collisionObj;
	DIRECTION direction;
	float entryTime;
};

