#include "Mario.h"
#include "MarioIdleState.h"
#include "MarioJumpState.h"
#include "../../Physic/CollisionManager.h"

Mario::Mario(): GameObject(new MarioIdleState())
{
	this->_showBoundingBox = true;
	this->velocity = VECTOR2D(0.0f, -100.0f);
}

void Mario::Update(float deltaTime)
{
	this->_isGrounded = false;
	CollisionManager* collision = CollisionManager::GetInstance();
	list<GameObject*> results = collision->RayCastWith(this, DIRECTION::DOWN, 10);
	for (GameObject* obj : results)
	{
		if (obj->name == "ground" || obj->name == "panel" || obj->name == "pine")
		{
			this->_isGrounded = true;
			DebugOut((wchar_t*)L"[INFO] Mario is GROUNDED \n");
		}
	}
	if (this->_isGrounded == false)
	{
		//not on ground
		this->velocity = VECTOR2D(0.0f, -100.0f);
		TransitionTo(new MarioJumpState());
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
	this->_state->OnKeyDown(keyCode);
}

void Mario::OnKeyUp(int keyCode)
{
	this->_state->OnKeyUp(keyCode);
}

void Mario::OnCollision(CollisionEvent colEvent)
{
	this->_state->OnCollision(colEvent);
	DebugOut((wchar_t*)L"[INFO] Collision entry time: %f, delta time: %f \n", colEvent.entryTimePercent, colEvent.deltaTime);
}

Animation* Mario::GetAnimation()
{
	string stateName = "super mario " + this->_state->name;

	AnimationService* animations = AnimationService::GetInstance();
	return animations->GetAnimation(stateName);
}
