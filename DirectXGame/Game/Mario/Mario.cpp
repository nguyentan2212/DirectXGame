#include "Mario.h"
#include "MarioRunState.h"
#include "MarioSitState.h"
#include "MarioIdleState.h"

Mario::Mario(): GameObject(new MarioIdleState())
{
	this->_showBoundingBox = true;
}

void Mario::Update(float deltaTime)
{
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
	this->_position += this->_velocity * colEvent.entryTimePercent * colEvent.deltaTime / 1000;
	this->_velocity.x = 0.0f;
}
