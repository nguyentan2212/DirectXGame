#pragma once
#include <dinput.h>
#include "../../Core/GameObject.h"

constexpr float MARIO_GRAVITY = 120;

constexpr float MARIO_X_ACCE = 80;
constexpr float MARIO_RUN_MAX_SPEED_X = 120;
constexpr float MARIO_JUMP_SPEED_Y = 100;
constexpr float MARIO_RUN_JUMP_SPEED_FACTOR_Y = 1.35f;
constexpr float MARIO_JUMP_DEFLECT_SPEED = 400;

constexpr int MARIO_SMALL = 0;
constexpr int MARIO_SUPER = 1;
constexpr int MARIO_RACCOON = 2;

constexpr float MARIO_SMALL_HEIGHT = 16.0f;
constexpr float MARIO_SMALL_WIDTH = 16.0f;

constexpr float MARIO_SUPER_HEIGHT = 28.0f;
constexpr float MARIO_SUPER_WIDTH = 16.0f;

constexpr float MARIO_RACCOON_HEIGHT = 28.0f;
constexpr float MARIO_RACCOON_WIDTH = 23.0f;

class Mario: public GameObject
{
public:
	Mario(ObjectState* state);

	void Update(float deltaTime) override;
	void Render() override;

	void OnKeyDown(int keyCode) override;
	void OnKeyUp(int keyCode) override;
	void OnCollision(CollisionEvent colEvent) override;

	void IncreaseScore(int score);
	void IncreaseCoin(int coin = 1);
	void UpdateRunSpeed(float speed);

private:
	Renderable* GetRenderable() override;

	void ChangeFigure(UINT figure);
	UINT _figure;
};

