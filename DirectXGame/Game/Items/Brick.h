#pragma once
#include "../../Core/GameObject.h"
#include "Text.h"

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
	Renderable* GetRenderable() override;
	Text* _text;
};