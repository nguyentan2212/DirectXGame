#include "Coin.h"

Coin::Coin(): GameObject(new ObjectState())
{
}

void Coin::Update(float deltaTime)
{
	GameObject::Update(deltaTime);
}

void Coin::OnCollision(CollisionEvent colEvent)
{
}

Animation* Coin::GetAnimation()
{
	AnimationService* animations = AnimationService::GetInstance();
	return animations->GetAnimation("coin");
}
