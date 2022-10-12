#pragma once
#include "../../Core/ObjectState.h"

class MarioRunState: public ObjectState
{
public:
	MarioRunState();
	void Update(float deltaTime) override;
	Animation* GetAnimation() override;

#pragma region Commands
	void Jump(float speed) override;
	void Idle() override;
	void Sit() override;
#pragma endregion

};

