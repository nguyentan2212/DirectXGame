#pragma once
#include "../../Core/GameObject.h"

constexpr float LEAF_GRAVITY = 300;
constexpr float LEAF_Y_SPEED = 200;

class Leaf : public GameObject
{
public:
	Leaf(VECTOR2D pos);

	void Update(float deltaTime) override;
	void Render() override;
	void OnCollision(CollisionEvent colEvent) override;

private:
	float _tempY = 20.0f;
	int _renderIndex = 0;
};

