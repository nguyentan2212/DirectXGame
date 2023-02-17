#include "CSceneWorldMap.h"
#include "CSceneOne.h"
#include <fstream>
#include "../../Core/KeyboardHandler.h"
#include "../../Core/Camera.h"
#include "../../Core/ObjectPool.h"

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
}

void CSceneWorldMap::OnChanged(UINT preSceneId)
{
	Camera* camera = Camera::GetInstance();
	camera->Follow(nullptr);

	camera->position = VECTOR2D(this->_tileWidth, this->_tileHeight);
	camera->bottomLeft = VECTOR2D(this->_tileWidth, this->_tileHeight);
	camera->topRight = VECTOR2D(this->_width * this->_tileWidth, this->_height * this->_tileHeight);
}
