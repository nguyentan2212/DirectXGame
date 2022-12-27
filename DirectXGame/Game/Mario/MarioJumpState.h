#pragma once
#include "../../Core/ObjectState.h"

class MarioJumpState: public ObjectState
{
public:
	MarioJumpState();
	void OnTransition() override;
	void Update(float deltaTime) override;
	void OnCollision(CollisionEvent colEvent) override;
	void OnKeyDown(int keyCode) override;
	void OnKeyUp(int keyCode) override;
};

