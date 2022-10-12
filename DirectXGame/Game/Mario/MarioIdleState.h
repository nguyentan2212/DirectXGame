#pragma once
#include "../../Core/ObjectState.h"
class MarioIdleState: public ObjectState
{
public:
	MarioIdleState();
	void Update(float deltaTime) override;
	Animation* GetAnimation() override;

#pragma region Commands
	void Run(float speed) override;
	void Jump(float speed) override;
	void Sit() override;
#pragma endregion

};

