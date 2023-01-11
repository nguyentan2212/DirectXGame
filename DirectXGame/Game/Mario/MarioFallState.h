#pragma once
#include "../../Core/State.h"

class MarioFallState: public State
{
public:
	MarioFallState();
	void OnTransition() override;
	void Update(float deltaTime) override;
	void OnCollision(CollisionEvent colEvent) override;
	void OnKeyDown(int keyCode) override;
};

