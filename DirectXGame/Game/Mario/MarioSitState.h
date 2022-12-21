#pragma once
#include "../../Core/ObjectState.h"

class MarioSitState: public ObjectState
{
public:
	MarioSitState();
	void OnTransition() override;
	void OnKeyUp(int keyCode) override;
	void OnChangeFigure() override;
};

