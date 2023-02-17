#include "CSceneOne.h"
#include <fstream>
#include "CSceneWorldMap.h"
#include "CSceneHidden.h"
#include "../Mario/Mario.h"
#include "../../Core/KeyboardHandler.h"
#include "../../Core/Camera.h"
#include "../../Physic/CollisionManager.h"
#include "../../Core/ObjectPool.h"
#include "../Items/Items.h"
#include "../Enemies/Enemies.h"

CSceneOne::CSceneOne(): Scene()
{
	string configPath = SCENE_ONE;
	this->_sceneId = SCENE_ONE_ID;
	fstream file(configPath);
	json config = json::parse(file);
	InitTilemap(config);
	InitObjects(config["objects"]);

	ObjectPool* pool = ObjectPool::GetInstance();
	pool->Clear();
	for (GameObject* obj : this->_objs)
	{
		pool->AddGameObject(obj);
	}
}

void CSceneOne::InitObjects(json config)
{
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
			else if (item["name"].get<string>() == "soft brick")
			{
				obj = Brick::CreateSoftBrick(position);
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
		else if (item["class"].get<string>() == "koopa troopa")
		{
			string name = item["name"].get<string>();
			if (name.find("giant") != string::npos)
			{
				obj = new KoopaTroopa(true);
			}
			else
			{
				obj = new KoopaTroopa(false);
			}
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
		this->_objs.push_back(obj);
	}
}

void CSceneOne::Update(float deltaTime)
{
	Scene::Update(deltaTime);
	KeyboardHandler* keyboard = KeyboardHandler::GetInstance();
	if (keyboard->IsKeyDown(DIK_LCONTROL) && keyboard->IsKeyDown(DIK_8))
	{
		this->_context->TransitionTo(SCENE_HIDDEN_ID);
	}
}

void CSceneOne::OnChanged(UINT preSceneId)
{
	ObjectPool* pool = ObjectPool::GetInstance();
	pool->Clear();
	for (GameObject* obj : this->_objs)
	{
		pool->AddGameObject(obj);
	}

	Camera* camera = Camera::GetInstance();

	GameObject* mario = pool->GetGameObjectWithClass("Mario");
	mario->SetState(SCENE_ONE_ID, "scene");

	if (preSceneId == SCENE_HIDDEN_ID)
	{
		GameObject* portal = pool->GetGameObjectWithName("portal out");
		mario->position = portal->position;
	}

	camera->bottomLeft = VECTOR2D(0.0f, -32.0f);
	camera->topRight = VECTOR2D(this->_width * this->_tileWidth, this->_height * this->_tileHeight);
	camera->Follow(mario);
}

void CSceneOne::CreateMario(VECTOR2D position)
{
	Mario* mario = new Mario();
	mario->position = VECTOR2D(650, 50);
	mario->SetState(SCENE_ONE_ID, "scene");
	//mario->position = position;

	KeyboardHandler* keyboard = KeyboardHandler::GetInstance();
	keyboard->AddListener(mario);

	Camera* camera = Camera::GetInstance();
	camera->Follow(mario);
	this->_objs.push_back(mario);
}
