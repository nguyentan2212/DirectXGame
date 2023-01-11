#pragma once
#include "../../Core/State.h"

constexpr float ATTACK_COOLDOWN = 600.0f;
class MarioAttackState: public State
{
public:
	MarioAttackState();

	void Update(float deltaTime) override;
	void OnTransition() override;
private:
	float _cooldown = ATTACK_COOLDOWN;
};

