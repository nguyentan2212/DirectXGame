#include "CSceneWorldMap.h"
#include "CSceneOne.h"
#include "../../Core/KeyboardHandler.h"
#include "../../Core/Camera.h"
#include "../../Core/ObjectPool.h"

CSceneWorldMap::CSceneWorldMap(): Scene(SCENE_WORLD_MAP)
{
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
