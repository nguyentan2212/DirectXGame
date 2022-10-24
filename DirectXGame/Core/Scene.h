#pragma once
#include <vector>
#include "GameObject.h"
#include "../Graphic/Sprite.h"
#include "../Utils/json.hpp"

using namespace::std;
using json = nlohmann::json;

class Scene
{
public:
	Scene(string configPath);

	virtual void Update(float deltaTime);
	virtual void Render();
	virtual void DrawBoundingBox();

protected:
	int _width;
	int _height;
	int _tileWidth;
	int _tileHight;

	vector<GameObject*> _gameObjects;
	vector<vector<Sprite*>> _tilemap;

	virtual void InitTilemap(json config);
	virtual void InitObjects(json config);
	virtual void RenderTileMap();
};

