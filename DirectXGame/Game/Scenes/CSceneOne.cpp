#include "CSceneOne.h"
#include <fstream>
#include "../Mario/Mario.h"
#include "../GUI.h"
#include "../../Core/KeyboardHandler.h"
#include "../../Core/Camera.h"
#include "../../Physic/CollisionManager.h"
#include "../Items/Brick.h"
#include "../Items/Coin.h"
CSceneOne::CSceneOne(string configPath): Scene()
{
	fstream file(configPath);
	json config = json::parse(file);
	this->_gameObjects = vector<GameObject*>(0);
	InitTilemap(config);
	InitObjects(config["objects"]);

	Mario* mario = new Mario();
	mario->position = VECTOR2D(900, 70);
	this->_gameObjects.push_back(mario);

	KeyboardHandler* keyboard = KeyboardHandler::GetInstance();
	keyboard->AddListener(mario);

	CollisionManager* collision = CollisionManager::GetInstance();
	collision->AddListener(mario);

	Camera* camera = Camera::GetInstance();
	camera->Follow(mario);
	camera->bottomLeft = VECTOR2D(0.0f, -32.0f);
	camera->topRight = VECTOR2D(this->_width * this->_tileWidth, this->_height * this->_tileHeight);

	mario->AddChildObject(new GUI);
}

void CSceneOne::InitObjects(json config)
{
	CollisionManager* collision = CollisionManager::GetInstance();
	for (json item : config)
	{
		GameObject* obj = nullptr;
		if (item["class"].get<string>() == "brick")
		{
			obj = new Brick();
		}
		else if (item["class"].get<string>() == "coin")
		{
			obj = new Coin();
		}
		else
		{
			obj = new GameObject(new ObjectState());
		}

		VECTOR2D position = VECTOR2D(item["x"], (float)this->_height * this->_tileHeight - item["y"]) - VECTOR2D(-item["width"].get<float>(), item["height"]) / 2.0f;
		obj->width = item["width"].get<float>();
		obj->height = item["height"].get<float>();
		obj->position = position;
		obj->name = obj->name.empty() ? item["name"].get<string>() : obj->name;
		obj->showBoundingBox = true;

		this->_gameObjects.push_back(obj);
		collision->AddListener(obj);
	}

}