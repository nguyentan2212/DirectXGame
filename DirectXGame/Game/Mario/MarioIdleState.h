#pragma once
#include "../../Core/State.h"
class MarioIdleState: public State
{
public:
	MarioIdleState();
	void Update(float deltaTime) override;
	void OnTransition() override;
	void OnKeyDown(int keyCode) override;
};

