#pragma once
#include "../../Core/GameObject.h"

constexpr float GOOMBA_SPEED = 30;

class Goomba: public GameObject
{
public:
	Goomba();

	void Render() override;
	void Update(float deltaTime) override;
	void OnCollision(CollisionEvent colEvent) override;

private:
	bool _isDeath;
	float _tempY;
	Animation* GetAnimation() override;

	void Death();
};

