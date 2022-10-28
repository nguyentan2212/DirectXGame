#pragma once
#include "../../Core/ObjectState.h"

constexpr float GRAVITY = -70;
class MarioJumpState: public ObjectState
{
public:
	MarioJumpState();
	void Update(float deltaTime) override;
	Animation* GetAnimation() override;
	void OnCollision(CollisionEvent colEvent) override;

#pragma region Commands
	void Run(float speed) override;
#pragma endregion

};

