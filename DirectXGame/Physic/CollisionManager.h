#pragma once
#include <list>
#include "CollisionEvent.h"
#include "../Utils/CMath.h"
#include "../Core/GameObject.h"

using namespace::std;

class CollisionManager
{
public:
	CollisionManager();

	static CollisionEvent CalcAABB(GameObject* objA, GameObject* objB, float deltaTime);
	static CollisionEvent CalcAABB(GameObject* objA, VECTOR2D vA, GameObject* objB, VECTOR2D vB, float deltaTime);
	static void Processing(GameObject* obj, float deltaTime);

	 static bool IsCollision(Box boxA, Box boxB);
};

