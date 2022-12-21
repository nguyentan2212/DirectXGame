#pragma once
#include "../../Core/ObjectState.h"

class MarioHoldState: public ObjectState
{
public:
	MarioHoldState();
	void OnTransition() override;
	void OnKeyDown(int keyCode) override;
	void OnKeyUp(int keyCode) override;
	void OnChangeFigure() override;
};

