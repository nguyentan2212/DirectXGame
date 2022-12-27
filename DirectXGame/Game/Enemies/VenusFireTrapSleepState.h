#pragma once
#include "../../Core/ObjectState.h"

class VenusFireTrapSleepState: public ObjectState
{
public:
	VenusFireTrapSleepState();

	void OnTransition() override;
	void Update(float deltaTime) override;
	void OnCollision(CollisionEvent colEvent) override;

private:
	float _y;
};

