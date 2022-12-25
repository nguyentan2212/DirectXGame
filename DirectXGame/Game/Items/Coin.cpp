#include "Coin.h"
#include "../Mario/Mario.h"

Coin::Coin(): GameObject(new ObjectState())
{
	this->_name = "coin";
}

void Coin::Update(float deltaTime)
{
	GameObject::Update(deltaTime);
}

void Coin::Render()
{
	GameObject::Render();
}

void Coin::OnCollision(CollisionEvent colEvent)
{
	Mario* mario = dynamic_cast<Mario*>(colEvent.collisionObj);

	if (mario != nullptr)
	{
		mario->IncreaseCoin();
		this->_isActive = false;
	}
}

Animation* Coin::GetAnimation()
{
	AnimationService* animations = AnimationService::GetInstance();
	return animations->GetAnimation("coin");
}
