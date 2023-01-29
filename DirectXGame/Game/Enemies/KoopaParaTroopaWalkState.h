#pragma once
#include "../../Core/State.h"

class KoopaParaTroopaWalkState: public State
{
public:
	KoopaParaTroopaWalkState();

	void OnTransition() override;
	void OnCollision(CollisionEvent colEvent) override;
};

