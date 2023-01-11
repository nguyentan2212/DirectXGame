#pragma once
#include "../../Core/State.h"

class KoopaParaTroopaStandState: public State
{
public:
	KoopaParaTroopaStandState();

	void OnTransition() override;
	void Update(float deltaTime) override;
	void OnCollision(CollisionEvent colEvent) override;

};

