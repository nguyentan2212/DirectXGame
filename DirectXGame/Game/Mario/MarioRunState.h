#pragma once
#include "../../Core/State.h"

class MarioRunState: public State
{
public:
	MarioRunState(int direction);
	void OnTransition() override;
	void OnCollision(CollisionEvent colEvent) override;
	void OnKeyDown(int keyCode) override;
	void OnKeyUp(int keyCode) override;
	void Update(float deltaTime) override;
private:
	int direction;
};

