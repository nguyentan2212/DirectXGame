#pragma once
#include "../../Core/GameObject.h"

constexpr float GOOMBA_SPEED = 30;
constexpr float GOOMBA_GRAVITY = 120;
constexpr float GOOMBA_SIZE = 16;

class Goomba: public GameObject
{
public:
	Goomba();
	void Update(float deltaTime) override;
	void OnCollision(CollisionEvent colEvent) override;

private:
	Renderable* GetRenderable() override;
	bool _isDeath;
};