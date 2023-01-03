#pragma once
#include "../../Core/ObjectState.h"

constexpr float KOOPA_PARATROOPA_WALK_SPEED_X = 40;

class KoopaParaTroopaWalkState: public ObjectState
{
public:
	KoopaParaTroopaWalkState();

	void OnTransition() override;
	void OnCollision(CollisionEvent colEvent) override;
};

