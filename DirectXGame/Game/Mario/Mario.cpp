#include "Mario.h"
#include "MarioIdleState.h"
#include "MarioJumpState.h"
#include "MarioFallState.h"
#include "MarioChangeFigureState.h"
#include "../GUI.h"
#include "../../Physic/CollisionManager.h"
#include "../../Core/KeyboardHandler.h"
#include "MarioDeathState.h"

Mario::Mario(): GameObject(new MarioIdleState())
{
	this->_showBoundingBox = true;
	this->_name = "small mario";
}

void Mario::Update(float deltaTime)
{
	if (this->_isActive == false)
	{
		return;
	}

	GameObject::Update(deltaTime);

	if (this->_velocity.x < 0)
	{
		this->_direction = DIRECTION::LEFT;
	}
	else if (this->_velocity.x > 0)
	{
		this->_direction = DIRECTION::RIGHT;
	}

	this->_acceleration = VECTOR2D(this->_acceleration.x, -MARIO_GRAVITY);
	this->_velocity += this->_acceleration * deltaTime / 1000;
	if (abs(this->_velocity.x) > MARIO_RUN_MAX_SPEED_X)
	{
		this->_velocity.x = this->_velocity.x > 0 ? MARIO_RUN_MAX_SPEED_X : -MARIO_RUN_MAX_SPEED_X;
	}

	this->_isGrounded = false;
	CollisionManager::Processing(this, deltaTime);
	this->_state->Update(deltaTime);

	Translate(this->_velocity * deltaTime / 1000);
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
	string objName = colEvent.collisionObj->name;
	if (objName == "pine" || objName == "ground" || objName == "cloud" || objName == "mushroom brick" || objName == "leaf brick")
	{
		if (colEvent.direction == Direction::DOWN)
		{
			this->_isGrounded = true;
			this->_position += this->_velocity * colEvent.entryTime;
			this->_velocity = VECTOR2D(this->_velocity.x, 0);
			this->_acceleration = VECTOR2D(this->_acceleration.x, 0.0f);
		}
	}
	this->_state->OnCollision(colEvent);
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

void Mario::UpdateRunSpeed(float speed)
{
	GameObject* temp = GetChildWithName("gui");
	if (temp != nullptr)
	{
		GUI* gui = dynamic_cast<GUI*>(temp);
		if (gui != nullptr)
		{
			gui->UpdateRunSpeed(abs(speed));
		}
	}
}

Animation* Mario::GetAnimation()
{
	string stateName = this->_name + " " + this->_state->name;

	AnimationService* animations = AnimationService::GetInstance();
	return animations->GetAnimation(stateName);
}
