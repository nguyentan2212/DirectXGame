#pragma once
#include "../../Core/GameObject.h"

constexpr float MUSHROOM_GRAVITY = 300;
constexpr float MUSHROOM_X_SPEED = 40;

class Mushroom: public GameObject
{
public:
	Mushroom(VECTOR2D pos);

	void Update(float deltaTime) override;
	void Render() override;
	void OnCollision(CollisionEvent colEvent) override;

private:
	float _tempY = 20.0f;
	int _renderIndex = 0;
};

