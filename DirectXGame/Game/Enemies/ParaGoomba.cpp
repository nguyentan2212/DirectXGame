#include "ParaGoomba.h"
#include "../../Graphic/SpriteService.h"
#include "../../Graphic/AnimationService.h"
#include "../../Physic/CollisionManager.h"

ParaGoomba::ParaGoomba(): GameObject()
{
	this->_width = PARAGOOMBA_WIDTH;
	this->_height = PARAGOOMBA_HEIGHT;
	this->_velocity = VECTOR2D(-PARAGOOMBA_SPEED_X, 0.0f);
	SetState(PARAGOOMBA_HAS_WING);

	AnimationService* anis = AnimationService::GetInstance();
	this->_leftWing = new GameObject(anis->GetAnimation("wing"));
	this->_rightWing = new GameObject(anis->GetAnimation("wing"));
	this->_rightWing->isFlipped = true;
}

void ParaGoomba::Render()
{
	if (this->_isActive == false)
	{
		return;
	}

	if (GetState() == PARAGOOMBA_HAS_WING)
	{
		this->_leftWing->Render();
		this->_rightWing->Render();
	}
	if (this->_score != nullptr)
	{
		this->_score->Render();
	}
	GameObject::Render();
}

void ParaGoomba::Update(float deltaTime)
{
	if (this->_isActive == false)
	{
		return;
	}

	if (GetState() == PARAGOOMBA_DEATH)
	{
		if (this->_deathDuration > 0)
		{
			this->_deathDuration -= deltaTime;
		}
		else
		{
			this->_isActive = false;
			this->_score->isActive = false;
		}
	}

	if (GetState() == PARAGOOMBA_HAS_WING)
	{
		this->_leftWing->Update(deltaTime);
		this->_leftWing->position = this->position + VECTOR2D(this->width / 2.0f, this->height / 2.0f);

		this->_rightWing->Update(deltaTime);
		this->_rightWing->position = this->position + VECTOR2D(-this->width / 2.0f, this->height / 2.0f);

		if (this->_runDuration > 0)
		{
			this->_runDuration -= deltaTime;
		}
		else if (this->_isGrounded)
		{
			if (this->_jumpCount < 2)
			{
				this->_jumpCount++;
				Jump(PARAGOOMBA_JUMP_SPEED);
			}
			else
			{
				this->_jumpCount = 0;
				this->_runDuration = PARAGOOMBA_RUN_DURATION;
				Jump(PARAGOOMBA_SUPER_JUMP_SPEED);
			}
		}
	}

	if (this->_score != nullptr)
	{
		if (this->_scoreDuration > 0)
		{
			this->_scoreDuration -= deltaTime;
			this->_score->Update(deltaTime);
		}
		else
		{
			this->_score->isActive = false;
			this->_scoreDuration = PARAGOOMBA_SCORE_DURATION;
		}
	}

	this->_acceleration = VECTOR2D(0.0f, -PARAGOOMBA_GRAVITY);
	this->_velocity += this->_acceleration * deltaTime / 1000;
	this->_isGrounded = false;
	CollisionManager::Processing(this, deltaTime);

	Translate(this->_velocity * deltaTime / 1000);
}

void ParaGoomba::OnCollision(CollisionEvent colEvent)
{
	string objName = colEvent.collisionObj->name;
	string className = typeid(*colEvent.collisionObj).name();
	if (className == "class Platform" || className == "class Brick")
	{
		if (colEvent.direction == Direction::DOWN)
		{
			Grounding(colEvent.entryTime);
		}
		else if (objName != "panel" && (colEvent.direction == Direction::LEFT || colEvent.direction == Direction::RIGHT))
		{
			this->_velocity = VECTOR2D(-this->_velocity.x, this->_velocity.y);
		}
	}

	if (GetState() == PARAGOOMBA_DEATH)
	{
		return;
	}

	if (objName == "mario")
	{
		if (colEvent.direction == DIRECTION::UP)
		{
			if (GetState() == PARAGOOMBA_HAS_WING)
			{
				Jump(0);
				SpriteService* sprites = SpriteService::GetInstance();
				this->_score = new GameObject(sprites->GetSprite("hub-and-font/400"));
				this->_score->position = this->position + VECTOR2D(0.0f, PARAGOOMBA_HEIGHT);
				SetState(PARAGOOMBA_LOST_WING);
			}
			else
			{
				SpriteService* sprites = SpriteService::GetInstance();
				this->_score = new GameObject(sprites->GetSprite("hub-and-font/1000"));
				this->_score->position = this->position + VECTOR2D(0.0f, PARAGOOMBA_HEIGHT);
				Death();
			}
		}
	}
}

void ParaGoomba::SetState(UINT stateValue, string stateName)
{
	this->_states[stateName] = stateValue;
}

Renderable* ParaGoomba::GetRenderable()
{
	if (GetState() == PARAGOOMBA_DEATH)
	{
		SpriteService* sprites = SpriteService::GetInstance();
		return sprites->GetSprite("enemies/paragoomba/2");
	}
	AnimationService* anis = AnimationService::GetInstance();
	return anis->GetAnimation("paragoomba walk");
}

void ParaGoomba::Jump(float speed)
{
	if (GetState() != PARAGOOMBA_HAS_WING)
	{
		return;
	}
	VECTOR2D vec = this->velocity;
	vec.y = speed;
	this->velocity = vec;
	this->acceleration = VECTOR2D(0.0f, 0.0f);
}

void ParaGoomba::Death()
{
	SetState(PARAGOOMBA_DEATH);
	this->velocity = VECTOR2D(0.0f, 0.0f);
	this->acceleration = VECTOR2D(0.0f, 0.0f);
	this->_height = PARAGOOMBA_DEATH_HEIGHT;
	this->_position = this->_position - VECTOR2D(0.0f, PARAGOOMBA_HEIGHT - PARAGOOMBA_DEATH_HEIGHT) / 2.0f;
	this->_leftWing->isActive = false;
	this->_rightWing->isActive = false;
}
