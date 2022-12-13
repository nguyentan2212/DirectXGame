#pragma once
#include "../../Core/ObjectState.h"

class MarioRunState: public ObjectState
{
public:
	MarioRunState();
	void OnCollision(CollisionEvent colEvent) override;
	void OnKeyDown(int keyCode) override;
	void OnKeyUp(int keyCode) override;
};

