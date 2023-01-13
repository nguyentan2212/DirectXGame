#pragma once
#include <dinput.h>
#include "MarioConst.h"
#include "../../Core/GameObject.h"


class Mario: public GameObject
{
public:
	Mario(State* state);

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
};

