#include "CSceneHidden.h"
#include "CSceneOne.h"
#include <fstream>
#include "../../Core/KeyboardHandler.h"
#include "../../Core/Camera.h"
#include "../../Core/ObjectPool.h"
#include "CSceneOne.h"
#include "../Items/Coin.h"
#include "../Items/Platform.h"

CSceneHidden::CSceneHidden(): Scene()
{
	string configPath = SCENE_HIDDEN;
	this->_sceneId = SCENE_HIDDEN_ID;
	fstream file(configPath);
	json config = json::parse(file);
	InitTilemap(config);
	InitObjects(config["objects"]);

	/*ObjectPool* pool = ObjectPool::GetInstance();
	pool->Clear();
	for (GameObject* obj : this->_objs)
	{
		pool->AddGameObject(obj);
	}*/

	Camera* camera = Camera::GetInstance();
	camera->Follow(nullptr);
	camera->position = VECTOR2D(0.0f, 0.0f);
}

void CSceneHidden::InitObjects(json config)
{
	for (json item : config)
	{
		VECTOR2D position = VECTOR2D(item["x"], (float)this->_height * this->_tileHeight - item["y"]) - VECTOR2D(-item["width"].get<float>(), item["height"]) / 2.0f;
		GameObject* obj = nullptr;

		if (item["class"].get<string>() == "coin")
		{
			obj = new Coin(position);
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
		this->_objs.push_back(obj);
	}
}

void CSceneHidden::Update(float deltaTime)
{
	Scene::Update(deltaTime);
	KeyboardHandler* keyboard = KeyboardHandler::GetInstance();
	if (keyboard->IsKeyDown(DIK_LCONTROL) && keyboard->IsKeyDown(DIK_7))
	{
		this->_context->TransitionTo(SCENE_ONE_ID);
	}
}

void CSceneHidden::OnChanged(UINT preSceneId)
{
	ObjectPool* pool = ObjectPool::GetInstance();

	GameObject* mario = pool->GetGameObjectWithClass("Mario");
	mario->SetState(SCENE_HIDDEN_ID, "scene");
	mario->isActive = true;
	pool->Clear();
	for (GameObject* obj : this->_objs)
	{
		pool->AddGameObject(obj);
	}
	pool->AddGameObject(mario);

	GameObject* portalIn = pool->GetGameObjectWithName("portal in");
	mario->position = portalIn->position - VECTOR2D(0.0f, mario->height / 2.0f);
	Camera* camera = Camera::GetInstance();
	camera->Follow(mario);
	camera->bottomLeft = VECTOR2D(0.0f, -32.0f);
	camera->topRight = VECTOR2D(this->_width * this->_tileWidth, this->_height * this->_tileHeight);
}
