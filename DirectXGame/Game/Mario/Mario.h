#pragma once
#include <dinput.h>
#include "MarioConst.h"
#include "../../Core/GameObject.h"


class Mario: public GameObject
{
public:
	Mario();

	void Update(float deltaTime) override;
	void Render() override;

	void OnKeyDown(int keyCode) override;
	void OnKeyUp(int keyCode) override;
	void OnCollision(CollisionEvent colEvent) override;

	void IncreaseScore(int score);
	void IncreaseCoin(int coin = 1);
	void UpdateRunSpeed(float speed);

	void SetState(UINT stateValue, string stateName = "default") override;
private:
	Renderable* GetRenderable() override;
	void ChangeFigure(UINT figure);

	void Idle();
	void Run(float acce_x);
	void Jump(float speed);
	void Fall();
	void Fly();
	void Sit();
	void Death();
	void Untouchable();
};

