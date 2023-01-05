#pragma once
#include "../../Core/ObjectState.h"

constexpr float ATTACK_COOLDOWN = 600.0f;
class MarioAttackState: public ObjectState
{
public:
	MarioAttackState();

	void Update(float deltaTime) override;
	void OnTransition() override;
private:
	float _cooldown = ATTACK_COOLDOWN;
};

