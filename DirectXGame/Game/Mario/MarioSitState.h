#pragma once
#include "../../Core/ObjectState.h"

class MarioSitState: public ObjectState
{
public:
	MarioSitState();
	void OnKeyUp(int keyCode) override;
};

