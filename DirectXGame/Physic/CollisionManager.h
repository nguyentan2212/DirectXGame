#pragma once
#include <list>
#include "../Utils/CMath.h"
#include "../Core/GameObject.h"

using namespace::std;

class CollisionManager
{
public:
	static CollisionManager* GetInstance();
	DIRECTION CalcAABB(GameObject* objA, GameObject* objB);
	bool IsCollision(Box boxA, Box boxB);
	void Processing();

	void AddListener(GameObject* listener);
	void RemoveListener(GameObject* listener);
private:
	CollisionManager();
	list<GameObject*> _listeners;

	static CollisionManager* _instance;
};

