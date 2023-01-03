#pragma once
#include "../../Core/ObjectState.h"

class MarioDeathState: public ObjectState
{
public:
	MarioDeathState();
	void Update(float deltaTime) override;
	void OnTransition() override;
};

