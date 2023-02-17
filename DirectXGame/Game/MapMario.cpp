#include "MapMario.h"
#include "Mario/MarioConst.h"
#include "../Physic/CollisionManager.h"

MapMario::MapMario(): GameObject()
{
	AnimationService* anis = AnimationService::GetInstance();
	this->_renderable = anis->GetAnimation("map mario");
}

void MapMario::Update(float deltaTime)
{
	CollisionManager::Processing(this, deltaTime);
	Translate(this->_velocity * deltaTime / 1000.0f);

	VECTOR2D distance = this->position - this->_portalPosition;
	float length = D3DXVec2Length(&distance);
	if (length <= PORTAL_SIZE)
	{
		this->canTeleport = true;
		DebugOut(L"[INFO] Collide with portal !\n");
	}
	else
	{
		this->canTeleport = false;
	}
}

void MapMario::OnKeyDown(int keyCode)
{
	if (this->_isActive == false)
	{
		return;
	}
	switch (keyCode)
	{
	case BTN_LEFT:
		this->_velocity = VECTOR2D(-MAP_MARIO_SPEED, 0.0f);
		break;
	case BTN_RIGHT:
		this->_velocity = VECTOR2D(MAP_MARIO_SPEED, 0.0f);
		break;
	case BTN_UP:
		this->_velocity = VECTOR2D(0.0f, MAP_MARIO_SPEED);
		break;
	case BTN_DOWN:
		this->_velocity = VECTOR2D(0.0f, -MAP_MARIO_SPEED);
		break;
	default:
		break;
	}
}

void MapMario::OnKeyUp(int keyCode)
{
	if (this->_isActive == false)
	{
		return;
	}
	switch (keyCode)
	{
	case BTN_LEFT:
	case BTN_RIGHT:
	case BTN_UP:
	case BTN_DOWN:
		this->_velocity = VECTOR2D(0.0f, 0.0f);
		break;
	default:
		break;
	}
}

void MapMario::OnCollision(CollisionEvent colEvent)
{
	string name = colEvent.collisionObj->name;
	if (name == "portal")
	{
		this->_portalPosition = colEvent.collisionObj->position;
	}
}
