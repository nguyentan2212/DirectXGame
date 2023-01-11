#pragma once
#include "../../Core/State.h"

class MarioFlyState: public State
{
public:
	MarioFlyState();
	void OnTransition() override;
	void Update(float deltaTime) override;
	void OnCollision(CollisionEvent colEvent) override;
	void OnKeyDown(int keyCode) override;
	void OnKeyUp(int keyCode) override;
};

