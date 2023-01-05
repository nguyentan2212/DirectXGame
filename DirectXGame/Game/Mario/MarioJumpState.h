#pragma once
#include "../../Core/ObjectState.h"

class MarioJumpState: public ObjectState
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

