#pragma once
#include "../../Core/ObjectState.h"

class KoopaParaTroopaStandState: public ObjectState
{
public:
	KoopaParaTroopaStandState();

	void OnTransition() override;
	void Update(float deltaTime) override;
	void OnCollision(CollisionEvent colEvent) override;

};

