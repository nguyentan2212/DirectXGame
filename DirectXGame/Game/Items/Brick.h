#pragma once
#include "../../Core/GameObject.h"

constexpr float BRICK_GRAVITY = 400;
constexpr float BRICK_BOUND_SPEED = 120;

class Brick: public GameObject
{
public:
	Brick(GameObject* content, VECTOR2D position);

	void Update(float deltaTime) override;
	void OnCollision(CollisionEvent colEvent) override;

private:
	Renderable* GetRenderable() override;
	GameObject* _content;
	float _beginY;
	bool _isTouched;
};