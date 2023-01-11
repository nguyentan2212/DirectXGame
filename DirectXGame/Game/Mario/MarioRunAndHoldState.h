#pragma once
#include "../../Core/State.h"

class MarioRunAndHoldState: public State
{
public:
	MarioRunAndHoldState(int direction);
	void OnTransition() override;
	void OnKeyDown(int keyCode) override;
	void OnKeyUp(int keyCode) override;

private:
	int direction;
};

