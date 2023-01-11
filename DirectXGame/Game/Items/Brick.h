#pragma once
#include "../../Core/GameObject.h"

constexpr float BRICK_GRAVITY = 400;
constexpr float BRICK_BOUND_SPEED = 120;
constexpr float BRICK_SIZE = 16;

class Brick: public GameObject
{
public:
	Brick(GameObject* content, VECTOR2D position);

	void Update(float deltaTime) override;
	void OnCollision(CollisionEvent colEvent) override;

	static Brick* CreateCoinBrick(VECTOR2D position);
	static Brick* CreateMushroomBrick(VECTOR2D position);
	static Brick* CreateLeafBrick(VECTOR2D position);

private:
	Renderable* GetRenderable() override;
	GameObject* _content;
	float _beginY;
	bool _isTouched;
};