#pragma once
#include "../../Core/State.h"

class MarioSitState: public State
{
public:
	MarioSitState();
	void OnTransition() override;
	void OnKeyUp(int keyCode) override;
};

