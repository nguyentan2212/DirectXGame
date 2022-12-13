#pragma once
#include "../../Core/ObjectState.h"

constexpr float GRAVITY = -100;
class MarioJumpState: public ObjectState
{
public:
	MarioJumpState();
	void OnCollision(CollisionEvent colEvent) override;
	void OnKeyDown(int keyCode) override;
	void OnKeyUp(int keyCode) override;
};

