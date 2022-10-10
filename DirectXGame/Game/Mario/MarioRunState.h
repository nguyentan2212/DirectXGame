#pragma once
#include "../../Core/ObjectState.h"

class MarioRunState: public ObjectState
{
public:
	MarioRunState();
	void Update(float deltaTime) override;
	Animation* GetAnimation() override;
};

