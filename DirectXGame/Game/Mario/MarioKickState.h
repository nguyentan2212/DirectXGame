#pragma once
#include "../../Core/State.h"

constexpr float KICK_COOLDOWN = 200.0f;
class MarioKickState: public State
{
public:
	MarioKickState();
	void Update(float deltaTime) override;
	void OnTransition() override;
	void OnKeyDown(int keyCode) override;
	void OnKeyUp(int keyCode) override;

private:
	float _cooldown = KICK_COOLDOWN;
};

