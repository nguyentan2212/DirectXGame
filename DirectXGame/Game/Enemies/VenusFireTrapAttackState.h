#pragma once
#include "../../Core/State.h"

constexpr float FIRE_TRAP_Y_SPEED = 30;
constexpr float FIRE_TRAP_X_DISTANCE_DETECT = 80;
constexpr float FIRE_TRAP_ATTACK_COOLDOWN = 2000;
constexpr float FIRE_BALL_SPEED = 50;
constexpr float FIRE_BALL_MAX_DISTANCE = 600;

class VenusFireTrapAttackState: public State
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

	void Attack(VECTOR2D target);
};

