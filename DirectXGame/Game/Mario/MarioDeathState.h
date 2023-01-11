#pragma once
#include "../../Core/State.h"

class MarioDeathState: public State
{
public:
	MarioDeathState();
	void Update(float deltaTime) override;
	void OnTransition() override;
};

