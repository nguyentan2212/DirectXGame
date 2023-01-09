#pragma once
#include <vector>
#include <string>
#include "GameObject.h"

class ObjectPool
{
public:
	static ObjectPool* GetInstance();
	GameObject* GetGameObjectWithName(string name);
	GameObject* GetGameObjectWithClass(string className);
	vector<GameObject*> GetAllGameObject();
	void AddGameObject(GameObject* obj);
	void Clear();
private:
	ObjectPool();
	~ObjectPool();

	vector<GameObject*> _objs;
	static ObjectPool* _instance;
};

