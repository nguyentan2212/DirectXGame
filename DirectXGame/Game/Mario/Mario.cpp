#include "Mario.h"
#include "MarioIdleState.h"
#include "MarioJumpState.h"
#include "MarioFallState.h"
#include "MarioChangeFigureState.h"
#include "../GUI.h"
#include "../../Physic/CollisionManager.h"
#include "../../Core/KeyboardHandler.h"

Mario::Mario(): GameObject(new MarioFallState())
{
	this->_showBoundingBox = true;
	this->_name = "small mario";
}

void Mario::Update(float deltaTime)
{
	CollisionManager* collision = CollisionManager::GetInstance();
	list<GameObject*> results = collision->RayCastWith(this, DIRECTION::DOWN, 10.0f, deltaTime);
	for (GameObject* obj : results)
	{
		if (obj->name == "ground" || obj->name == "panel" || obj->name == "pine" || obj->name == "cloud")
		{
			this->_isGrounded = true;
		}
	}
	if (this->_isGrounded == false && this->_state->name != "jump" && 
		this->_state->name != "fall" && this->_state->name != "fly")
	{
		//not on ground
		TransitionTo(new MarioFallState());
	}
	if (this->_velocity.x < 0)
	{
		this->_direction = DIRECTION::LEFT;
	}
	else if (this->_velocity.x > 0)
	{
		this->_direction = DIRECTION::RIGHT;
	}
	this->_state->Update(deltaTime);
	GameObject::Update(deltaTime);
	if (abs(this->_velocity.x) > MARIO_RUN_MAX_SPEED_X)
	{
		this->_velocity.x = this->_velocity.x > 0 ? MARIO_RUN_MAX_SPEED_X : -MARIO_RUN_MAX_SPEED_X;
	}
	this->_isGrounded = false;
	//DebugOut((wchar_t*)L"[INFO] Mario vel.x = %f, vel.y = %f, acc.x = %f, acc.y = %f \n", _velocity.x, _velocity.y, _acceleration.x, _acceleration.y);
}

void Mario::Render()
{
	_isFlipped = this->_direction == DIRECTION::LEFT ? false : true;
	GameObject::Render(-0.1);
}

void Mario::OnKeyDown(int keyCode)
{
	KeyboardHandler* keyboard = KeyboardHandler::GetInstance();
	if (keyCode == DIK_X && keyboard->IsKeyDown(DIK_LCONTROL) && this->_name != "small mario")
	{
		TransitionTo(new MarioChangeFigureState("small mario"));
	}
	else if (keyCode == DIK_R && keyboard->IsKeyDown(DIK_LCONTROL))
	{
		TransitionTo(new MarioChangeFigureState("raccoon mario"));
	}
	else if (keyCode == DIK_S && keyboard->IsKeyDown(DIK_LCONTROL))
	{
		TransitionTo(new MarioChangeFigureState("super mario"));
	}
	this->_state->OnKeyDown(keyCode);
}

void Mario::OnKeyUp(int keyCode)
{
	this->_state->OnKeyUp(keyCode);
}

void Mario::OnCollision(CollisionEvent colEvent)
{
	this->_state->OnCollision(colEvent);
	if (colEvent.collisionObj->name == "pine")
	{
		this->_position += this->_velocity * colEvent.entryTimePercent * colEvent.deltaTime / 1000;
		this->_velocity = VECTOR2D(0, 0);
		this->_acceleration = VECTOR2D(0.0f, 0.0f);
		if (colEvent.direction != Direction::DOWN)
		{
			TransitionTo(new MarioFallState());
		}
	}
	DebugOut((wchar_t*)L"[INFO] Collision entry time: %f, delta time: %f \n", colEvent.entryTimePercent, colEvent.deltaTime);
}

void Mario::IncreaseScore(int score)
{
	GameObject* temp = GetChildWithName("gui");
	if (temp != nullptr)
	{
		GUI* gui = dynamic_cast<GUI*>(temp);
		if (gui != nullptr)
		{
			gui->IncreaseScore(score);
		}
	}
}

void Mario::IncreaseCoin(int coin)
{
	GameObject* temp = GetChildWithName("gui");
	if (temp != nullptr)
	{
		GUI* gui = dynamic_cast<GUI*>(temp);
		if (gui != nullptr)
		{
			gui->IncreaseCoin(coin);
		}
	}
}

Animation* Mario::GetAnimation()
{
	string stateName = this->_name + " " + this->_state->name;

	AnimationService* animations = AnimationService::GetInstance();
	return animations->GetAnimation(stateName);
}
