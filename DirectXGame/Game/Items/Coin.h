#pragma once
#include "../../Core/GameObject.h"

class Coin: public GameObject
{
public:
	Coin();

	void Update(float deltaTime) override;
	void OnCollision(CollisionEvent colEvent) override;

private:
	bool _isActive = true;
	Animation* GetAnimation() override;
};

