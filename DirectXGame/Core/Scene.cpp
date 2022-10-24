#include "Scene.h"
#include <string>
#include <fstream>
#include "EmptyObjectState.h"
#include "../Graphic/SpriteService.h"
#include "../Graphic/Graphic.h"

Scene::Scene(string configPath)
{
	fstream file(configPath);
	json config = json::parse(file);
	this->_gameObjects = vector<GameObject*>(0);
	InitTilemap(config);
}

void Scene::Update(float deltaTime)
{
	for (GameObject* obj : this->_gameObjects)
	{
		obj->Update(deltaTime);
	}
}

void Scene::Render()
{
	for (int i = 0; i < this->_width; i++)
	{
		for (int j = 0; j < this->_height; j++)
		{
			if (this->_tilemap[j][i] != nullptr)
			{
				float x = i * this->_tileWidth + this->_tileWidth / 2.0f;
				float y = j * this->_tileHight + this->_tileHight / 2.0f;
				this->_tilemap[j][i]->Draw(VECTOR2D(x, y));
			}
		}
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
	this->_tileHight = config["tileheight"];
	this->_tileWidth = config["tilewidth"];
	string tileset = config["tileset"]["name"].get<string>();

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
			index--;
			this->_tilemap[row][col] = sprites->GetSprite(tileset, index);
		}
		count++;
	}
	InitObjects(config["objects"]);
}

void Scene::InitObjects(json config)
{
	for (json item : config)
	{
		GameObject* obj = new GameObject(new EmptyObjectState(item["width"], item["height"]));
		obj->position = VECTOR2D(item["x"], (float)this->_height * this->_tileHight - item["y"]) - VECTOR2D(-item["width"].get<float>(), item["height"]) / 2.0f;
		obj->name = item["name"].get<string>();
		obj->showBoundingBox = true;
		this->_gameObjects.push_back(obj);
	}
}
