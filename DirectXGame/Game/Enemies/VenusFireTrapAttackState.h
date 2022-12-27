#pragma once
#include "../../Core/ObjectState.h"

constexpr float FIRE_TRAP_Y_SPEED = 30;
constexpr float FIRE_TRAP_X_DISTANCE_DETECH = 60;
constexpr float FIRE_TRAP_ATTACK_COOLDOWN = 3000;

class VenusFireTrapAttackState: public ObjectState
{
public:
	VenusFireTrapAttackState(Direction direction);

	void OnTransition() override;
	void Update(float deltaTime) override;
	void OnCollision(CollisionEvent colEvent) override;

private:
	Direction _direction;
	float _y;
	float _cooldown;

	void Attack();
};

