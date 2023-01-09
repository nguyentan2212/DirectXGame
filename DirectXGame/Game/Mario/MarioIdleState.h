#pragma once
#include "../../Core/ObjectState.h"
class MarioIdleState: public ObjectState
{
public:
	MarioIdleState();
	void Update(float deltaTime) override;
	void OnTransition() override;
	void OnKeyDown(int keyCode) override;

	static int count;
};

