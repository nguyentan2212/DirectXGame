#pragma once
#include <vector>
#include "CMath.h"
#include "../Core/GameObject.h"

constexpr int MAX_LEVEL = 5;
constexpr int MAX_OBJECT_IN_REGION = 4;

class Quadtree
{
public:
	Quadtree();
	Quadtree(int level, Box region);
	~Quadtree();

	void Clear();
	void Insert(GameObject* obj);
	vector<GameObject*> Retrieve(GameObject* obj);
	vector<GameObject*> GetAllGameObject();
	bool IsContain(GameObject* obj);

	static Quadtree* CreateQuadtree(std::vector<GameObject*> objs);
private:
	int _level;
	Box _region;
	vector<GameObject*> _objs;

	Quadtree* _topLeft;
	Quadtree* _topRight;
	Quadtree* _bottomLeft;
	Quadtree* _bottomRight;

	void Split();
};

