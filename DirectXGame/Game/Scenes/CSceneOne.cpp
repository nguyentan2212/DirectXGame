#include "CSceneOne.h"
#include <fstream>
#include "CSceneWorldMap.h"
#include "../Mario/Mario.h"
#include "../Mario/MarioIdleState.h"
#include "../GUI.h"
#include "../../Core/KeyboardHandler.h"
#include "../../Core/Camera.h"
#include "../../Physic/CollisionManager.h"
#include "../Items/Brick.h"
#include "../Items/Coin.h"
#include "../../Core/ObjectPool.h"
#include "../Enemies/VenusFireTrap.h"
#include "../Enemies/Goomba.h"
#include "../Enemies/KoopaParaTroopa.h"
#include "../Enemies/ParaGoomba.h"
#include "../Items/Mushroom.h"

CSceneOne::CSceneOne(): Scene()
{
	ObjectPool* pool = ObjectPool::GetInstance();
	pool->Clear();

	string configPath = SCENE_ONE;
	fstream file(configPath);
	json config = json::parse(file);
	InitTilemap(config);
	InitObjects(config["objects"]);

	Mario* mario = new Mario(new MarioIdleState());
	mario->position = VECTOR2D(550, 50);
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

	VenusFireTrap* trap = new VenusFireTrap();
	trap->position = VECTOR2D(367, 45);
	pool->AddGameObject(trap);
}

void CSceneOne::InitObjects(json config)
{
	ObjectPool* pool = ObjectPool::GetInstance();
	for (json item : config)
	{
		VECTOR2D position = VECTOR2D(item["x"], (float)this->_height * this->_tileHeight - item["y"]) - VECTOR2D(-item["width"].get<float>(), item["height"]) / 2.0f;

		GameObject* obj = nullptr;
		if (item["class"].get<string>() == "brick")
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
		/*else if (item["class"].get<string>() == "koopaparatroopa")
		{
			obj = new KoopaParaTroopa();
		}
		else if (item["class"].get<string>() == "paragoomba")
		{
			obj = new ParaGoomba();
		}*/
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
