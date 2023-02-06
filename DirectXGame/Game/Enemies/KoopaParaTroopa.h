#pragma once
#include "../../Core/GameObject.h"
#include "../Items/Head.h"

constexpr float KOOPA_PARATROOPA_WIDTH = 16;
constexpr float KOOPA_PARATROOPA_HEIGHT = 26;
constexpr float KOOPA_PARATROOPA_RUN_SPEED_X = 80;
constexpr float KOOPA_PARATROOPA_WALK_SPEED_X = 20;
constexpr float KOOPA_PARATROOPA_GRAVITY = 120;

constexpr UINT KOOPA_PARATROOPA_WALK = 0;
constexpr UINT KOOPA_PARATROOPA_RUN = 1;
constexpr UINT KOOPA_PARATROOPA_STUN = 2;
constexpr UINT KOOPA_PARATROOPA_IS_HELD = 3;

class KoopaParaTroopa: public GameObject
{
public: 
	KoopaParaTroopa();

	void Update(float deltaTime) override;
	void Render() override;
	void OnCollision(CollisionEvent colEvent) override;
	void SetState(UINT stateValue, string stateName = "default") override;

private:
	float _tempY = 0.0f;
	Renderable* GetRenderable() override;
	Head* _head = nullptr;

	void Stun();
};

