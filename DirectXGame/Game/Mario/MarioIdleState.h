#pragma once
#include "../../Core/ObjectState.h"
class MarioIdleState: public ObjectState
{
public:
	MarioIdleState();
	void OnTransition() override;
	void OnKeyDown(int keyCode) override;
};

