#include "CSceneOne.h"
#include "../Mario/Mario.h"
#include "../../Core/KeyboardHandler.h"
#include "../../Core/Camera.h"
#include "../../Physic/CollisionManager.h"

CSceneOne::CSceneOne(string configPath): Scene(configPath)
{
	Mario* mario = new Mario();
	mario->position = VECTOR2D(30, 50);
	this->_gameObjects.push_back(mario);

	KeyboardHandler* keyboard = KeyboardHandler::GetInstance();
	keyboard->AddListener(mario);

	CollisionManager* collision = CollisionManager::GetInstance();
	collision->AddListener(mario);

	Camera* camera = Camera::GetInstance();
	camera->Follow(mario);
	camera->bottomLeft = VECTOR2D(0.0f, -32.0f);
	camera->topRight = VECTOR2D(this->_width * this->_tileWidth, this->_height * this->_tileHeight);
}
