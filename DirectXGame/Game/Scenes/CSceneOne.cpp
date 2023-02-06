#include "CSceneOne.h"
#include <fstream>
#include "CSceneWorldMap.h"
#include "../Mario/Mario.h"
#include "../GUI.h"
#include "../../Core/KeyboardHandler.h"
#include "../../Core/Camera.h"
#include "../../Physic/CollisionManager.h"
#include "../../Core/ObjectPool.h"
#include "../Items/Items.h"
#include "../Enemies/Enemies.h"

CSceneOne::CSceneOne(): Scene()
{
	ObjectPool* pool = ObjectPool::GetInstance();
	pool->Clear();

	string configPath = SCENE_ONE;
	fstream file(configPath);
	json config = json::parse(file);
	InitTilemap(config);
	InitObjects(config["objects"]);
}

void CSceneOne::InitObjects(json config)
{
	ObjectPool* pool = ObjectPool::GetInstance();
	for (json item : config)
	{
		VECTOR2D position = VECTOR2D(item["x"], (float)this->_height * this->_tileHeight - item["y"]) - VECTOR2D(-item["width"].get<float>(), item["height"]) / 2.0f;

		GameObject* obj = nullptr;
		if (item["class"].get<string>() == "mario")
		{
			CreateMario(position);
			continue;
		}
		else if (item["class"].get<string>() == "brick")
		{
			if (item["name"].get<string>() == "mushroom brick")
			{
				obj = Brick::CreateMushroomBrick(position);
			}
			else if (item["name"].get<string>() == "leaf brick")
			{
				obj = Brick::CreateLeafBrick(position);
			}
			else
			{
				obj = Brick::CreateCoinBrick(position);
			}
		}
		else if (item["class"].get<string>() == "coin")
		{
			obj = new Coin(position);
		}
		else if (item["class"].get<string>() == "goomba")
		{
			obj = new Goomba();
		}
		else if (item["class"].get<string>() == "koopa paratroopa")
		{
			obj = new KoopaParaTroopa();
			obj->name = item["name"].get<string>();
		}
		else if (item["class"].get<string>() == "venus fire trap")
		{
			obj = new VenusFireTrap(position, item["name"].get<string>());
			obj->name = item["name"].get<string>();
		}
		else if (item["class"].get<string>() == "para goomba")
		{
			obj = new ParaGoomba();
		}
		else if (item["class"].get<string>() == "platform")
		{
			obj = new Platform();
			obj->width = item["width"].get<float>();
			obj->height = item["height"].get<float>();
			obj->name = item["name"].get<string>();
		}
		else
		{
			obj = new GameObject();
			obj->width = item["width"].get<float>();
			obj->height = item["height"].get<float>();
			obj->name = item["name"].get<string>();
		}
		obj->position = position;
		obj->showBoundingBox = true;
		pool->AddGameObject(obj);
	}
}

void CSceneOne::Update(float deltaTime)
{
	Scene::Update(deltaTime);
	KeyboardHandler* keyboard = KeyboardHandler::GetInstance();
	if (keyboard->IsKeyDown(DIK_LCONTROL) && keyboard->IsKeyDown(DIK_0))
	{
		this->_context->TransitionTo(new CSceneWorldMap());
	}
}

void CSceneOne::CreateMario(VECTOR2D position)
{
	ObjectPool* pool = ObjectPool::GetInstance();

	Mario* mario = new Mario();
	mario->position = VECTOR2D(1000, 100);
	//mario->position = position;
	pool->AddGameObject(mario);

	KeyboardHandler* keyboard = KeyboardHandler::GetInstance();
	keyboard->AddListener(mario);

	Camera* camera = Camera::GetInstance();
	camera->Follow(mario);
	camera->bottomLeft = VECTOR2D(0.0f, -32.0f);
	camera->topRight = VECTOR2D(this->_width * this->_tileWidth, this->_height * this->_tileHeight);

	GUI* gui = new GUI();
	mario->AddChildObject(gui);
	pool->AddGameObject(gui);
}
