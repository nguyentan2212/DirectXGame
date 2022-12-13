#pragma once
#include "../../Core/ObjectState.h"
class MarioIdleState: public ObjectState
{
public:
	MarioIdleState();
	void OnKeyDown(int keyCode) override;
};

