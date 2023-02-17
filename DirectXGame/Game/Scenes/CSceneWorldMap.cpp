#include "CSceneWorldMap.h"
#include "CSceneOne.h"
#include <fstream>
#include "../../Core/KeyboardHandler.h"
#include "../../Core/Camera.h"
#include "../../Core/ObjectPool.h"
#include "../../Graphic/SpriteService.h"
#include "../MapMonster.h"
#include "../MapMario.h"

CSceneWorldMap::CSceneWorldMap(): Scene(SCENE_WORLD_MAP)
{
	string configPath = SCENE_WORLD_MAP;
	this->_sceneId = SCENE_WORLD_MAP_ID;
	fstream file(configPath);
	json config = json::parse(file);
	InitTilemap(config);
	InitObjects(config["objects"]);

	ObjectPool* pool = ObjectPool::GetInstance();
	pool->Clear();

	Camera* camera = Camera::GetInstance();
	camera->Follow(nullptr);
	camera->position = VECTOR2D(0.0f, 0.0f);
}

void CSceneWorldMap::Update(float deltaTime)
{
	Scene::Update(deltaTime);
	KeyboardHandler* keyboard = KeyboardHandler::GetInstance();
	ObjectPool* pool = ObjectPool::GetInstance();
	MapMario* obj = dynamic_cast<MapMario*>(pool->GetGameObjectWithName("start"));

	if (keyboard->IsKeyDown(DIK_K) && obj->canTeleport == true)
	{
		obj->isActive = false;
		this->_context->TransitionTo(SCENE_ONE_ID);
	}
}

void CSceneWorldMap::OnChanged(UINT preSceneId)
{
	ObjectPool* pool = ObjectPool::GetInstance();
	pool->Clear();
	for (GameObject* obj : this->_objs)
	{
		pool->AddGameObject(obj);
	}

	Camera* camera = Camera::GetInstance();
	camera->Follow(nullptr);

	camera->position = VECTOR2D((float)this->_tileWidth, (float)this->_tileHeight);
	camera->bottomLeft = VECTOR2D((float)this->_tileWidth, (float)this->_tileHeight);
	camera->topRight = VECTOR2D((float)this->_width * this->_tileWidth, (float)this->_height * this->_tileHeight);
}

void CSceneWorldMap::InitObjects(json config)
{
	AnimationService* anis = AnimationService::GetInstance();
	SpriteService* sprites = SpriteService::GetInstance();
	KeyboardHandler* keyboard = KeyboardHandler::GetInstance();

	for (json item : config)
	{
		VECTOR2D position = VECTOR2D(item["x"], (float)this->_height * this->_tileHeight - item["y"]) - VECTOR2D(-item["width"].get<float>(), item["height"]) / 2.0f;

		GameObject* obj = nullptr;
		if (item["class"].get<string>() == "glass")
		{
			obj = new GameObject(anis->GetAnimation("glass"));
		}
		else if (item["name"].get<string>() == "monster")
		{
			obj = new MapMonster(position);
		}
		else if (item["name"].get<string>() == "help-text")
		{
			obj = new GameObject(sprites->GetSprite("world-map-143"));
		}
		else if (item["name"].get<string>() == "start")
		{
			obj = new MapMario();
			keyboard->AddListener(obj);
		}
		else
		{
			obj = new GameObject();
		}
		obj->width = item["width"].get<float>();
		obj->height = item["height"].get<float>();
		obj->name = item["name"].get<string>();
		obj->position = position;
		obj->showBoundingBox = false;
		this->_objs.push_back(obj);
	}
}
