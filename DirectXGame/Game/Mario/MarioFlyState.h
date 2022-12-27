#pragma once
#include "../../Core/ObjectState.h"

class MarioFlyState: public ObjectState
{
public:
	MarioFlyState();
	void OnTransition() override;
	void Update(float deltaTime) override;
	void OnCollision(CollisionEvent colEvent) override;
	void OnKeyDown(int keyCode) override;
	void OnKeyUp(int keyCode) override;
};

