#pragma once
#include "../../Core/State.h"

class MarioHoldState: public State
{
public:
	MarioHoldState();
	void OnTransition() override;
	void OnKeyDown(int keyCode) override;
	void OnKeyUp(int keyCode) override;
};

