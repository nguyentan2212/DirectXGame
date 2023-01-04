#pragma once
#include "../../Core/ObjectState.h"

constexpr float PARAGOOMBA_SPEED_Y = 80;
constexpr float PARAGOOMBA_GRAVITY = 100;
constexpr float PARAGOOMBA_JUMP_COOLDOWN = 500.0f;
constexpr int PARAGOOMBA_JUMP_COUNT = 3;

class ParaGoombaJumpState: public ObjectState
{
public:
	ParaGoombaJumpState();

	void Update(float deltaTime) override;
	void OnTransition() override;
	void OnCollision(CollisionEvent colEvent) override;

private:
	float _cooldown = PARAGOOMBA_JUMP_COOLDOWN;
	int _jumptCount = 0;
};

