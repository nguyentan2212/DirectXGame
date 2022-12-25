#pragma once
#include <list>
#include "CollisionEvent.h"
#include "../Utils/CMath.h"
#include "../Core/GameObject.h"

using namespace::std;

class CollisionManager
{
public:
	static CollisionManager* GetInstance();
	CollisionEvent CalcAABB(GameObject* objA, GameObject* objB, float deltaTime);
	CollisionEvent CalcAABB(GameObject* objA, VECTOR2D vA, GameObject* objB, VECTOR2D vB, float deltaTime);

	bool IsCollision(Box boxA, Box boxB);
	void Processing(float deltaTime);

	bool RayCastBetween(GameObject* objA, GameObject* objB, DIRECTION direction, float distance, float deltaTime);
	list<GameObject*> RayCastWith(GameObject* objRoot, DIRECTION direction, float distance, float deltaTime);

	void AddListener(GameObject* listener);
	void RemoveListener(GameObject* listener);
private:
	CollisionManager();
	list<GameObject*> _listeners;

	static CollisionManager* _instance;
};

