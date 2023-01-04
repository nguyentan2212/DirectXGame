#include "Goomba.h"
#include "../../Core/Camera.h"
#include "../../Graphic/SpriteService.h"
#include "../../Physic/CollisionManager.h"
#include "../Mario/Mario.h"
#include "../Mario/MarioJumpState.h"
#include "../Mario/MarioChangeFigureState.h"
#include "../Mario/MarioDeathState.h"

Goomba::Goomba(): GameObject(new ObjectState())
{
	this->_name = "goomba";
	this->_width = 16;
	this->_height = 16;
	this->_isDeath = false;
	this->_velocity = VECTOR2D(-GOOMBA_SPEED, 0.0f);
}

void Goomba::Render()
{
	if (this->_isActive == false)
	{
		return;
	}

	if (this->_isDeath == false)
	{
		GameObject::Render();
		return;
	}
	SpriteService* sprites = SpriteService::GetInstance();
	Sprite* sprite = sprites->GetSprite("enemies/goomba/2");

	Camera* camera = Camera::GetInstance();
	VECTOR2D pos = GetWorldPosition() - camera->position;
	sprite->Draw(pos, false, -0.1f);

	// draw score
	sprite = sprites->GetSprite("hub-and-font/100");
	sprite->Draw(pos + VECTOR2D(0.0f, this->_tempY));
}

void Goomba::Update(float deltaTime)
{
	if (this->_isActive == false)
	{
		return;
	}

	if (this->_isDeath)
	{
		if (this->_tempY <= 80.0f)
		{
			this->_tempY += GOOMBA_SPEED * 1.5f * deltaTime / 1000;
			DebugOut((wchar_t*)L"[INFO] Goomba tempY = %f \n", _tempY);
		}
		else
		{
			this->_isActive = false;
		}
	}

	GameObject::Update(deltaTime);

	VECTOR2D pos = GetWorldPosition();
	if (pos.x <= -10.0f || pos.y <= -40.0f)
	{
		this->_isActive = false;
	}
}

void Goomba::OnCollision(CollisionEvent colEvent)
{
	string className = typeid(*colEvent.collisionObj).name();

	if (colEvent.collisionObj->name == "ground" || colEvent.collisionObj->name == "pine" || 
		colEvent.collisionObj->name == "border" || className == "class Brick")
	{
		if (colEvent.direction == Direction::LEFT || colEvent.direction == Direction::RIGHT)
		{
			this->_velocity = VECTOR2D(-this->_velocity.x, this->_velocity.y);
		}
		else if (colEvent.direction == Direction::DOWN)
		{
			this->_velocity = VECTOR2D(this->_velocity.x, 0.0f);
		}
	}
	else if (this->_isDeath == false)
	{
		Mario* mario = dynamic_cast<Mario*>(colEvent.collisionObj);
		if (mario != nullptr)
		{
			string stateName = mario->GetStateName();
			if (stateName == "death")
			{
				return;
			}
			if (colEvent.direction == Direction::UP)
			{
				this->_isDeath = true;
				this->_velocity = VECTOR2D(0.0f, 0.0f);
				VECTOR2D pos = GetWorldPosition();
				pos.y -= 6.0f;
				this->position = pos;
				this->_height = 9.0f;

				mario->TransitionTo(new MarioJumpState());
			}
			else if (mario->name != "small mario" && stateName.find("change figure") == string::npos)
			{
				mario->TransitionTo(new MarioChangeFigureState("small mario"));
			}
			else if (stateName.find("change figure") == string::npos)
			{
				mario->TransitionTo(new MarioDeathState());
			}
		}
	}
}

Animation* Goomba::GetAnimation()
{
	AnimationService* anis = AnimationService::GetInstance();
	return anis->GetAnimation("goomba walk");
}
