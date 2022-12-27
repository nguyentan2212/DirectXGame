#pragma once
#include <vector>
#include "GameObject.h"
#include "GameEngine.h"
#include "../Graphic/Sprite.h"
#include "../Utils/json.hpp"

using namespace::std;
using json = nlohmann::json;

class Scene
{
public:
	Scene() {};
	Scene(string configPath);
	~Scene();

	virtual void Update(float deltaTime);
	virtual void Render();
	virtual void DrawBoundingBox();

	W_PROPERTY(GameEngine*, context);
	SET(context) { this->_context = value; }

protected:
	GameEngine* _context;

	int _width;
	int _height;
	int _tileWidth;
	int _tileHeight;

	vector<vector<Sprite*>> _tilemap;
	vector<string> _tilesetNames;
	vector<int> _tilesetFirstIds;

	virtual void InitTilemap(json config);
	virtual void InitObjects(json config);
	virtual void RenderTileMap();
};

