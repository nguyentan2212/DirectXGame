#pragma once
#include "../../Core/State.h"

class VenusFireTrapSleepState: public State
{
public:
	VenusFireTrapSleepState();

	void OnTransition() override;
	void Update(float deltaTime) override;
	void OnCollision(CollisionEvent colEvent) override;

private:
	float _y;
};

