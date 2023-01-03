#include "KoopaParaTroopa.h"
#include "KoopaParaTroopaWalkState.h"
#include "KoopaParaTroopaStandState.h"


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
}

void KoopaParaTroopa::Render()
{
	_isFlipped = this->_direction == DIRECTION::LEFT ? false : true;
	GameObject::Render();
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
