#pragma once
#include "../../Core/GameObject.h"

constexpr float BRICK_GRAVITY = 500;
constexpr float BRICK_BOUND_SPEED = 120;
class Brick: public GameObject
{
public:
	Brick();

	void Update(float deltaTime) override;
	void Render() override;
	void OnCollision(CollisionEvent colEvent) override;

private:
	bool _isTouched = false;
	float _y = 0.0f;
	float _tempVY = 200.0f;
	float _tempY = 21.0f;
	int _renderIndex = 0;
	Animation* GetAnimation() override;
};

