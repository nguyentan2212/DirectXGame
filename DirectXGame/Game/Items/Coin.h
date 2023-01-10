#pragma once
#include "../../Core/GameObject.h"

constexpr float COIN_SPEED = 120;
constexpr float COIN_GRAVITY = 100;
constexpr float COIN_SIZE = 16;

constexpr float SCORE_SPEED = 40;
constexpr float SCORE_MAX_LENGHT = 60;

class Coin: public GameObject
{
public:
	Coin(VECTOR2D position);

	void Update(float deltaTime) override;
	void OnCollision(CollisionEvent colEvent) override;

	static Coin* ScoreCoin(VECTOR2D position);

private:
	Renderable* GetRenderable() override;
	GameObject* _score;
};

