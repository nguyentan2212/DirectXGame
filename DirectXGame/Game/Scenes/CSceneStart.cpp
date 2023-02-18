#include "CSceneStart.h"
#include "CSceneWorldMap.h"
#include "../../Graphic/SpriteService.h"
#include "../../Core/Camera.h"
#include "../../Core/KeyboardHandler.h"

CSceneStart::CSceneStart()
{
	SpriteService* sprites = SpriteService::GetInstance();
	this->_background = sprites->GetSprite("start-scene");

	Camera* camera = Camera::GetInstance();
	camera->Follow(nullptr);
	camera->position = VECTOR2D(0.0f, 0.0f);
}

void CSceneStart::Update(float deltaTime)
{
	Scene::Update(deltaTime);
	KeyboardHandler* keyboard = KeyboardHandler::GetInstance();

	if (keyboard->IsKeyDown(DIK_K))
	{
		this->_context->TransitionTo(SCENE_WORLD_MAP_ID);
	}
}

void CSceneStart::OnChanged(UINT preSceneId)
{
}

void CSceneStart::Render()
{
	this->_background->Render(this->_background->width / 2.0f, this->_background->height / 2.0f);
}
