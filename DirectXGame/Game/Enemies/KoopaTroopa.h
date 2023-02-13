#pragma once
#include "../../Core/GameObject.h"
#include "../Items/Head.h"

constexpr float KOOPA_TROOPA_WIDTH = 16;
constexpr float KOOPA_TROOPA_HEIGHT = 26;
constexpr float KOOPA_TROOPA_RUN_SPEED_X = 80;
constexpr float KOOPA_TROOPA_WALK_SPEED_X = 28;
constexpr float KOOPA_TROOPA_JUMP_SPEED = 140;
constexpr float KOOPA_TROOPA_GRAVITY = 120;
constexpr float KOOPA_TROOPA_RUN_DURATION = 1400;
constexpr float KOOPA_TROOPA_REMOVE_HEAD_DISTANCE = 200;

constexpr UINT KOOPA_TROOPA_WALK = 0;
constexpr UINT KOOPA_TROOPA_RUN = 1;
constexpr UINT KOOPA_TROOPA_STUN = 2;
constexpr UINT KOOPA_TROOPA_IS_HELD = 3;
constexpr UINT KOOPA_TROOPA_JUMP = 4;

constexpr UINT KOOPA_TROOPA_HAS_WING = 0;
constexpr UINT KOOPA_TROOPA_LOST_WING = 1;

class KoopaTroopa: public GameObject
{
public:
	KoopaTroopa(bool hasWing = false);

	void Update(float deltaTime) override;
	void Render() override;
	void OnCollision(CollisionEvent colEvent) override;
	void SetState(UINT stateValue, string stateName = "default") override;

private:
	float _tempY = 0.0f;
	Renderable* GetRenderable() override;
	Head* _head = nullptr;
	float _runDuration = KOOPA_TROOPA_RUN_DURATION;

	GameObject* _score = nullptr;
	GameObject* _wing = nullptr;

	void Jump(float speed);
	void ToggleHead();
	void Jump();

};

