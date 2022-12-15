#pragma once
#include "../../Core/ObjectState.h"

class MarioKickState: public ObjectState
{
public:
	MarioKickState();
	void OnKeyDown(int keyCode) override;
	void OnKeyUp(int keyCode) override;
};
