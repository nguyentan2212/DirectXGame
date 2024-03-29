#include "Scene.h"
#include <string>
#include <fstream>
#include "KeyboardHandler.h"
#include "Camera.h"
#include "ObjectPool.h"
#include "../Physic/CollisionManager.h"
#include "../Graphic/SpriteService.h"

Scene::Scene(string configPath)
{
	/*fstream file(configPath);
	json config = json::parse(file);
	InitTilemap(config);
	InitObjects(config["objects"]);

	ObjectPool* pool = ObjectPool::GetInstance();
	for (GameObject* obj : this->_objs)
	{
		pool->AddGameObject(obj);
	}*/
}

Scene::~Scene()
{
	
}

void Scene::Update(float deltaTime)
{
	Camera* camera = Camera::GetInstance();
	camera->Update(deltaTime);

	KeyboardHandler* keyboard = KeyboardHandler::GetInstance();
	keyboard->Processing();

	ObjectPool* pool = ObjectPool::GetInstance();
	vector<GameObject*> objs = pool->GetAllGameObject(true);
	for (GameObject* obj : objs)
	{
		obj->Update(deltaTime);
	}
	AnimationService* anis = AnimationService::GetInstance();
	anis->Update(deltaTime);
}

void Scene::Render()
{
	RenderTileMap();
	ObjectPool* pool = ObjectPool::GetInstance();
	vector<GameObject*> objs = pool->GetAllGameObject(true);
	for (GameObject* obj : objs)
	{
		if (obj->name == "score coin")
		{
			DebugOut(L"[INFO] score coin!\n");
		}
		obj->Render();
	}
}

void Scene::DrawBoundingBox()
{
	ObjectPool* pool = ObjectPool::GetInstance();
	vector<GameObject*> objs = pool->GetAllGameObject(true);
	for (GameObject* obj : objs)
	{
		if (obj->showBoundingBox)
		{
			obj->DrawBoundingBox();
		}
	}
}

void Scene::OnChanged(UINT preSceneId)
{
}

void Scene::InitTilemap(json config)
{
	this->_height = config["height"];
	this->_width = config["width"];
	this->_tileHeight = config["tileheight"];
	this->_tileWidth = config["tilewidth"];
	//string tileset = config["tileset"]["name"].get<string>();
	for (json item : config["tileset"])
	{
		this->_tilesetNames.push_back(item["name"].get<string>());
		this->_tilesetFirstIds.push_back(item["firstgid"].get<int>());
	}

	SpriteService* sprites = SpriteService::GetInstance();

	this->_tilemap = vector<vector<Sprite*>>(this->_height);
	for (int i = 0; i < this->_height; i++)
	{
		this->_tilemap[i] = vector<Sprite*>(this->_width);
	}

	int count = 0;
	for (int index : config["data"])
	{
		// change input data from top-down to bottom-up
		int col = count % this->_width;
		int row = this->_height - count / this->_width - 1;		

		if (index > 0)
		{
			int i = 0;
			while (i < this->_tilesetFirstIds.size() && index >= this->_tilesetFirstIds[i])
			{
				i++;
			}
			i--;
			/*if (i != 0)
			{
				DebugOut(L"[ERROR] first id error: '%d' at index: '%d'!\n", i, index);
			}*/
			index -= this->_tilesetFirstIds[i];
			this->_tilemap[row][col] = sprites->GetSprite(this->_tilesetNames[i], index);
		}
		count++;
	}
}

void Scene::InitObjects(json config)
{
	for (json item : config)
	{
		GameObject* obj = new GameObject();
		obj->width = item["width"].get<float>();
		obj->height = item["height"].get<float>();
		obj->position = VECTOR2D(item["x"], (float)this->_height * this->_tileHeight - item["y"]) - VECTOR2D(-item["width"].get<float>(), item["height"]) / 2.0f;
		obj->name = item["name"].get<string>();
		obj->showBoundingBox = true;
		this->_objs.push_back(obj);
	}
}

void Scene::RenderTileMap()
{
	Camera* camera = Camera::GetInstance();
	VECTOR2D cameraPosition = camera->position;

	for (int i = 0; i < this->_width; i++)
	{
		for (int j = 0; j < this->_height; j++)
		{
			if (this->_tilemap[j][i] != nullptr && camera->IsDrawable(Box(i * this->_tileWidth, j * this->_tileHeight, this->_tileWidth, this->_tileHeight)))
			{
				
				float tileCenterX = max(this->_tileWidth, this->_tilemap[j][i]->width) / 2.0f;
				float tileCenterY = max(this->_tileHeight, this->_tilemap[j][i]->height) / 2.0f;

				float x = i * this->_tileWidth + tileCenterX;
				float y = j * this->_tileHeight + tileCenterY;
				this->_tilemap[j][i]->Render(VECTOR2D(x, y) - cameraPosition, false, 0.3);
			}
		}
	}
}
