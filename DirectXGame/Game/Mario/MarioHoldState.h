#pragma once
#include "../../Core/ObjectState.h"

class MarioHoldState: public ObjectState
{
public:
	MarioHoldState();
	void OnKeyDown(int keyCode) override;
	void OnKeyUp(int keyCode) override;
};

