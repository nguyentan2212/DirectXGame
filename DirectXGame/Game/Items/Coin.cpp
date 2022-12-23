#include "Coin.h"

Coin::Coin(): GameObject(new ObjectState())
{
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
	string st = typeid(*colEvent.collisionObj).name();
	if (st == "class Mario")
	{
		this->_isActive = false;
	}
}

Animation* Coin::GetAnimation()
{
	AnimationService* animations = AnimationService::GetInstance();
	return animations->GetAnimation("coin");
}
