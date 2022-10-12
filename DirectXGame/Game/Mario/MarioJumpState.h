#pragma once
#include "../../Core/ObjectState.h"

class MarioJumpState: public ObjectState
{
public:
	MarioJumpState();
	void Update(float deltaTime) override;
	Animation* GetAnimation() override;

#pragma region Commands
	void Run(float speed) override;
	void Idle() override;
#pragma endregion

};

