#pragma once
#include "../../Core/ObjectState.h"

constexpr float PARAGOOMBA_SPEED_X = 25;
constexpr float PARAGOOMBA_WALK_COOLDOWN = 2000.0f;

class ParaGoombaNormalState: public ObjectState
{
public:
	ParaGoombaNormalState(int direction);

	void Update(float deltaTime) override;
	void OnTransition() override;
	void OnCollision(CollisionEvent colEvent) override;

private:
	float _cooldown = PARAGOOMBA_WALK_COOLDOWN;
	int _direction;
};

