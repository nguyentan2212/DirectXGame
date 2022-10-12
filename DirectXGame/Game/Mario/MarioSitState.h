#pragma once
#include "../../Core/ObjectState.h"

class MarioSitState: public ObjectState
{
public:
	MarioSitState();
	void Update(float deltaTime) override;
	Animation* GetAnimation() override;

#pragma region Commands
	void Idle() override;
#pragma endregion

};

