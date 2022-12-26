#pragma once
#include <vector>
#include <string>
#include "GameObject.h"
#include "../Utils/Quadtree.h"

class ObjectPool
{
public:
	static ObjectPool* GetInstance();
	GameObject* GetGameObjectWithName(string name);
	vector<GameObject*> GetAllGameObject();
	vector<GameObject*> GetAllGameObjectWithQuadtree(GameObject* obj);
	vector<GameObject*> GetAllGameObjectWithQuadtree();
	void AddGameObject(GameObject* obj);
	void Clear();
	void SetQuadtree(Quadtree* quadtree);
private:
	ObjectPool();
	~ObjectPool();
	Quadtree* _quadtree;

	vector<GameObject*> _objs;
	static ObjectPool* _instance;
};

