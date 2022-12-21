#pragma once
#include "../../Core/ObjectState.h"

class MarioRunAndHoldState: public ObjectState
{
public:
	MarioRunAndHoldState(int direction);
	void OnTransition() override;
	void OnKeyDown(int keyCode) override;
	void OnKeyUp(int keyCode) override;
	void OnChangeFigure() override;

private:
	int direction;
};

