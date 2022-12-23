#pragma once
#include "../../Core/GameObject.h"

class Coin: public GameObject
{
public:
	Coin();

	void Update(float deltaTime) override;
	void Render() override;
	void OnCollision(CollisionEvent colEvent) override;

private:
	Animation* GetAnimation() override;
};

