#pragma once
#include "../../Core/GameObject.h"

constexpr float GOOMBA_SPEED = 30;
constexpr float GOOMBA_GRAVITY = 120;
constexpr float GOOMBA_SIZE = 16;
constexpr float GOOMBA_DEATH_HEIGHT = 9;
constexpr float GOOMBA_DEATH_DURATION = 1000;

class Goomba: public GameObject
{
public:
	Goomba();
	void Update(float deltaTime) override;
	void OnCollision(CollisionEvent colEvent) override;

private:
	Renderable* GetRenderable() override;
	bool _isDeath;
	float _deathDuration = GOOMBA_DEATH_DURATION;
};