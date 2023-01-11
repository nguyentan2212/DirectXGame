#pragma once
#include "../../Core/State.h"

constexpr float KOOPA_PARATROOPA_WALK_SPEED_X = 40;

class KoopaParaTroopaWalkState: public State
{
public:
	KoopaParaTroopaWalkState();

	void OnTransition() override;
	void OnCollision(CollisionEvent colEvent) override;
};

