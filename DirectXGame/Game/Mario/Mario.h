#pragma once
#include <dinput.h>
#include "../../Core/GameObject.h"

constexpr float MARIO_GRAVITY = 120;

constexpr float MARIO_X_ACCE = 80;
constexpr float MARIO_RUN_MAX_SPEED_X = 120;
constexpr float MARIO_JUMP_SPEED_Y = 100;
constexpr float MARIO_JUMP_DEFLECT_SPEED = 400;

class Mario: public GameObject
{
public:
	Mario();

	void Update(float deltaTime) override;
	void Render() override;

	void OnKeyDown(int keyCode) override;
	void OnKeyUp(int keyCode) override;
	void OnCollision(CollisionEvent colEvent) override;

private:
	bool _isGrounded = false;
	Animation* GetAnimation() override;
};

