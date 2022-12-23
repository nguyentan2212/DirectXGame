#pragma once
#include "../../Core/GameObject.h"

constexpr float BRICK_GRAVITY = 500;
constexpr float BRICK_BOUND_SPEED = 120;
class Brick: public GameObject
{
public:
	Brick();

	void Update(float deltaTime) override;
	void OnCollision(CollisionEvent colEvent) override;

private:
	bool _isTouched = true;
	float _y = 0.0f;
	Animation* GetAnimation() override;
};

