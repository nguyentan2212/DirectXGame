#pragma once
#include "../Utils/CMath.h"

class GameObject;
class CollisionEvent
{
public:
	CollisionEvent(GameObject* obj, DIRECTION direction, float entryTimePercent, float deltatime);
	~CollisionEvent();

	static CollisionEvent NoCollision();

	GameObject* collisionObj;
	DIRECTION direction;
	float entryTimePercent;
	float deltaTime;
};

