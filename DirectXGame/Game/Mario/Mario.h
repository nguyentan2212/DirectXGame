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
	void Grounding(float time) override;
	void ChangeFigure(UINT figure);

	void Idle();
	void Run(float direction);
	void Jump(float speed);
	void Fly();
	void Sit();
	void Death();
	void Untouchable();
	void Hold();
	void Kick();

	void OnCollisionWithPlatform(CollisionEvent colEvent);
	void OnCollisionWithBrick(CollisionEvent colEvent);
	void OnCollisionWithItem(CollisionEvent colEvent);
	void OnCollisionWithGoomba(CollisionEvent colEvent);
	void OnCollisionWithParaGoomba(CollisionEvent colEvent);
	void OnCollisionWithKoopaParaTroopa(CollisionEvent colEvent);
	void OnCollisionWithKoopaTroopa(CollisionEvent colEvent);

	bool IsKeyDown(int keyCode);

	GameObject* _holdObj = nullptr;
	float _kickTime = KICK_TIME;
	float _untouchableTime = UNTOUCHABLE_TIME;
	float _flyingTime;
	UINT _blockMask;
	string _preFigure;
};

