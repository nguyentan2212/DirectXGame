#include "KoopaParaTroopa.h"
#include "KoopaParaTroopaWalkState.h"
#include "KoopaParaTroopaStandState.h"
#include "../../Core/Camera.h"
#include "../../Graphic/SpriteService.h"

KoopaParaTroopa::KoopaParaTroopa(): GameObject(new KoopaParaTroopaWalkState())
{
	this->_name = "koopa paratroopa";
	this->_width = 16;
	this->_height = 26;
}

void KoopaParaTroopa::Update(float deltaTime)
{
	this->_state->Update(deltaTime);
	GameObject::Update(deltaTime);
	if (this->_velocity.x < 0)
	{
		this->_direction = DIRECTION::LEFT;
	}
	else if (this->_velocity.x > 0)
	{
		this->_direction = DIRECTION::RIGHT;
	}
	if (this->_state->name == "stand" && this->_tempY <= 80.0f)
	{
		this->_tempY += 45.0f * deltaTime / 1000;
	}
}

void KoopaParaTroopa::Render()
{
	_isFlipped = this->_direction == DIRECTION::LEFT ? false : true;
	GameObject::Render();

	if (this->_state->name == "stand" && this->_tempY <= 80.0f)
	{
		Camera* camera = Camera::GetInstance();
		VECTOR2D pos = GetWorldPosition() - camera->position;

		SpriteService* sprites = SpriteService::GetInstance();
		Sprite* sprite = sprites->GetSprite("hub-and-font/100");
		sprite->Draw(pos + VECTOR2D(0.0f, this->_tempY));
	}
}

void KoopaParaTroopa::OnCollision(CollisionEvent colEvent)
{
	this->_state->OnCollision(colEvent);
}

Animation* KoopaParaTroopa::GetAnimation()
{
	AnimationService* anis = AnimationService::GetInstance();
	string stateName = this->_state->name;
	return anis->GetAnimation("koopa paratroopa " + stateName);
}
