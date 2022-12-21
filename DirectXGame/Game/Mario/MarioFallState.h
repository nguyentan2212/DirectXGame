#pragma once
#include "../../Core/ObjectState.h"

class MarioFallState: public ObjectState
{
public:
	MarioFallState();
	void OnTransition() override;
	void Update(float deltaTime) override;
	void OnCollision(CollisionEvent colEvent) override;
	void OnChangeFigure() override;
};

