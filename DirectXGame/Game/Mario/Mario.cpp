#include "Mario.h"
#include "MarioRunState.h"
#include "MarioSitState.h"
#include "MarioIdleState.h"
#include "../../Physic/CollisionManager.h"

Mario::Mario(): GameObject(new MarioIdleState())
{
	this->_showBoundingBox = true;
	this->_state->Jump(0);
}

void Mario::Update(float deltaTime)
{
	this->_isGrounded = false;
	CollisionManager* collision = CollisionManager::GetInstance();
	list<GameObject*> results = collision->RayCastWith(this, DIRECTION::DOWN, 30);
	for (GameObject* obj : results)
	{
		if (obj->name == "ground" || obj->name == "panel" || obj->name == "pine")
		{
			this->_isGrounded = true;
			DebugOut((wchar_t*)L"[INFO] Mario is GROUNDED \n");
		}
	}
	if (this->_isGrounded == false && this->_velocity.y <= 0)
	{
		this->_state->Jump(0);
	}
	if (this->_velocity.x < 0)
	{
		this->_direction = DIRECTION::LEFT;
	}
	else if (this->_velocity.x > 0)
	{
		this->_direction = DIRECTION::RIGHT;
	}
	GameObject::Update(deltaTime);
}

void Mario::Render()
{
	_isFlipped = this->_direction == DIRECTION::LEFT ? false : true;
	GameObject::Render();
}

void Mario::OnKeyDown(int keyCode)
{
	switch (keyCode)
	{
	case DIK_UP:
		DebugOut((wchar_t*)L"[INFO] Key input UP \n");
		this->_state->Jump(SPEED);
		break;
	case DIK_DOWN:
		DebugOut((wchar_t*)L"[INFO] Key input DOWN \n");
		this->_state->Sit();
		break;
	case DIK_LEFT:
		DebugOut((wchar_t*)L"[INFO] Key input LEFT \n");
		this->_state->Run(-SPEED);
		break;
	case DIK_RIGHT:
		DebugOut((wchar_t*)L"[INFO] Key input RIGHT \n");
		this->_state->Run(SPEED);
		break;
	default:
		this->_state->Idle();
		break;
	}
}

void Mario::OnKeyUp(int keyCode)
{
	switch (keyCode)
	{
	case DIK_UP:
	case DIK_DOWN:
	case DIK_LEFT:
	case DIK_RIGHT:
		this->_state->Idle();
		break;
	default:
		break;
	}
}

void Mario::OnCollision(CollisionEvent colEvent)
{
	this->_state->OnCollision(colEvent);
	DebugOut((wchar_t*)L"[INFO] Collision entry time: %f, delta time: %f \n", colEvent.entryTimePercent, colEvent.deltaTime);
}