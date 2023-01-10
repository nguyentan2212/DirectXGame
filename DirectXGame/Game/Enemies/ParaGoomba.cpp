#include "ParaGoomba.h"
#include "../../Core/Camera.h"
#include "../../Graphic/SpriteService.h"
#include "ParaGoombaNormalState.h"
#include "../Mario/Mario.h"
#include "../Mario/MarioJumpState.h"
#include "../Mario/MarioChangeFigureState.h"
#include "../Mario/MarioDeathState.h"

ParaGoomba::ParaGoomba(): GameObject(new ParaGoombaNormalState(-1))
{
	this->_name = "paragoomba";
	this->_velocity = VECTOR2D(-PARAGOOMBA_SPEED_X, 0.0f);
	SpriteService* sprites = SpriteService::GetInstance();
	this->_lostWingScore = sprites->GetSprite("hub-and-font/400");
	this->_deathScore = sprites->GetSprite("hub-and-font/800");
}

void ParaGoomba::Render()
{
	if (this->_isActive == false)
	{
		return;
	}
	GameObject::Render();

	Camera* camera = Camera::GetInstance();
	VECTOR2D pos = GetWorldPosition() - camera->position;

	SpriteService* sprites = SpriteService::GetInstance();

	Sprite* sprite = sprites->GetSprite("hub-and-font/400");

	if (this->isLostWings && !this->isDeath && this->_lostWingScore != nullptr)
	{
		// draw score
		sprite->Render(pos + VECTOR2D(0.0f, this->_tempY));
		return;
	}
	else if (this->isDeath && this->_deathScore != nullptr)
	{
		sprite = sprites->GetSprite("enemies/paragoomba/2");
		sprite->Render(pos, false, -0.1f);

		// draw score
		sprite = sprites->GetSprite("hub-and-font/800");
		sprite->Render(pos + VECTOR2D(0.0f, this->_tempY));
		return;
	}

	if (this->isLostWings)
	{
		return;
	}

	if (this->_state->name == "normal")
	{
		sprite = sprites->GetSprite("enemies/wing-1");
		sprite->Render(pos + VECTOR2D(8.0f, 8.0f), false, -0.1f);
		sprite->Render(pos + VECTOR2D(-8.0f, 8.0f), true, -0.1f);
		return;
	}

	AnimationService* anis = AnimationService::GetInstance();
	Animation* ani = anis->GetAnimation("wing");

	ani->Render(pos + VECTOR2D(8.0f, 8.0f), false, -0.1f);
	ani->Render(pos + VECTOR2D(-8.0f, 8.0f), true, -0.1f);
}

void ParaGoomba::Update(float deltaTime)
{
	if (this->_isActive == false)
	{
		return;
	}

	this->_state->Update(deltaTime);
	GameObject::Update(deltaTime);

	VECTOR2D pos = GetWorldPosition();
	if (pos.x <= -10.0f || pos.y <= -40.0f)
	{
		this->_isActive = false;
	}

	AnimationService* anis = AnimationService::GetInstance();
	Animation* ani = anis->GetAnimation("wing");
	ani->Update(deltaTime);

	if (this->isLostWings && !this->isDeath)
	{
		if (this->_tempY <= 80.0f && this->_lostWingScore != nullptr)
		{
			this->_tempY += 45.0f * deltaTime / 1000;
			//DebugOut((wchar_t*)L"[INFO] Para Goomba tempY = %f \n", _tempY);
		}
		else
		{
			this->_tempY = 0.0f;
			this->_lostWingScore = nullptr;
		}
	}
	else if (this->isDeath)
	{
		if (this->_tempY <= 80.0f && this->_deathScore != nullptr)
		{
			this->_tempY += 45.0f * deltaTime / 1000;
			//DebugOut((wchar_t*)L"[INFO] Para Goomba tempY = %f \n", _tempY);
		}
		else
		{
			this->_tempY = 0.0f;
			this->_deathScore = nullptr;
			this->_isActive = false;
		}
	}
}

void ParaGoomba::OnCollision(CollisionEvent colEvent)
{
	this->_state->OnCollision(colEvent);

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
			IsAttacked();
			if (this->isLostWings)
			{
				mario->IncreaseScore(800);
			}
			else
			{
				mario->IncreaseScore(400);
			}
			mario->TransitionTo(new MarioJumpState(0.5f));
		}
		else if (mario->GetStateName() == "attack")
		{
			if (this->isLostWings)
			{
				mario->IncreaseScore(800);
			}
			else
			{
				mario->IncreaseScore(400);
			}
			IsAttacked();
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

Renderable* ParaGoomba::GetRenderable()
{
	AnimationService* anis = AnimationService::GetInstance();
	return anis->GetAnimation("paragoomba walk");
}

void ParaGoomba::IsAttacked()
{
	if (this->isLostWings)
	{
		this->isDeath = true;
		this->_velocity = VECTOR2D(0.0f, 0.0f);
		VECTOR2D pos = GetWorldPosition();
		this->position = pos;
		this->_height = 9.0f;
	}
	else
	{
		this->isLostWings = true;
	}
}
