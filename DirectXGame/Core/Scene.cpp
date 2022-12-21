#include "Scene.h"
#include <string>
#include <fstream>
#include "KeyboardHandler.h"
#include "Camera.h"
#include "../Physic/CollisionManager.h"
#include "../Graphic/SpriteService.h"

Scene::Scene(string configPath)
{
	fstream file(configPath);
	json config = json::parse(file);
	this->_gameObjects = vector<GameObject*>(0);
	InitTilemap(config);
}

void Scene::Update(float deltaTime)
{
	KeyboardHandler* keyboard = KeyboardHandler::GetInstance();
	keyboard->Processing();

	CollisionManager* collision = CollisionManager::GetInstance();
	collision->Processing(deltaTime);

	for (GameObject* obj : this->_gameObjects)
	{
		obj->Update(deltaTime);
	}
	Camera* camera = Camera::GetInstance();
	camera->Update(deltaTime);
}

void Scene::Render()
{
	RenderTileMap();
	for (GameObject* obj : this->_gameObjects)
	{
		obj->Render();
	}
}

void Scene::DrawBoundingBox()
{
	for (GameObject* obj : this->_gameObjects)
	{
		obj->DrawBoundingBox();
	}
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
	InitObjects(config["objects"]);
}

void Scene::InitObjects(json config)
{
	CollisionManager* collision = CollisionManager::GetInstance();
	for (json item : config)
	{
		GameObject* obj = new GameObject(new ObjectState());
		obj->width = item["width"].get<float>();
		obj->height = item["height"].get<float>();
		obj->position = VECTOR2D(item["x"], (float)this->_height * this->_tileHeight - item["y"]) - VECTOR2D(-item["width"].get<float>(), item["height"]) / 2.0f;
		obj->name = item["name"].get<string>();
		obj->showBoundingBox = true;
		this->_gameObjects.push_back(obj);
		collision->AddListener(obj);
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
			if (this->_tilemap[j][i] != nullptr)
			{
				float tileCenterX = max(this->_tileWidth, this->_tilemap[j][i]->width) / 2.0f;
				float tileCenterY = max(this->_tileHeight, this->_tilemap[j][i]->height) / 2.0f;

				float x = i * this->_tileWidth + tileCenterX;
				float y = j * this->_tileHeight + tileCenterY;
				this->_tilemap[j][i]->Draw(VECTOR2D(x, y) - cameraPosition);
			}
		}
	}
}
