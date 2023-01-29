#pragma once
#include "../../Core/GameObject.h"
#include "../Items/Head.h"

constexpr float KOOPA_PARATROOPA_WIDTH = 16;
constexpr float KOOPA_PARATROOPA_HEIGHT = 26;
constexpr float KOOPA_PARATROOPA_RUN_SPEED_X = 65;
constexpr float KOOPA_PARATROOPA_WALK_SPEED_X = 30;
constexpr float KOOPA_PARATROOPA_GRAVITY = 120;

class KoopaParaTroopa: public GameObject
{
public: 
	KoopaParaTroopa();

	void Update(float deltaTime) override;
	void Render() override;
	void OnCollision(CollisionEvent colEvent) override;

private:
	float _tempY = 0.0f;
	Renderable* GetRenderable() override;
	Head* _head;
};

