#pragma once
#include "../../Core/State.h"

class MarioJumpState: public State
{
public:
	MarioJumpState(float speedFactor = 1.0f);
	void OnTransition() override;
	void Update(float deltaTime) override;
	void OnCollision(CollisionEvent colEvent) override;
	void OnKeyDown(int keyCode) override;
	void OnKeyUp(int keyCode) override;

private:
	float _speedFactor = 1.0f;
};

