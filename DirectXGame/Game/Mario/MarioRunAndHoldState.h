#pragma once
#include "../../Core/ObjectState.h"

class MarioRunAndHoldState: public ObjectState
{
public:
	MarioRunAndHoldState();
	void OnKeyDown(int keyCode) override;
	void OnKeyUp(int keyCode) override;
};

