#include "CSceneOne.h"
#include "../Mario/Mario.h"
#include "../../Core/KeyboardHandler.h"
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
}
