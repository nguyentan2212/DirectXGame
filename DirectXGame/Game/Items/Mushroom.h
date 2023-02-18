#pragma once
#include "../../Core/GameObject.h"

constexpr float MUSHROOM_GRAVITY = 100;
constexpr float MUSHROOM_X_SPEED = 30;
constexpr float MUSHROOM_Y_SPEED = 10;
constexpr float MUSHROOM_SIZE = 16;

constexpr float MUSHROOM_SCORE_SPEED = 20;
constexpr float MUSHROOM_SCORE_MAX_LENGHT = 80;
constexpr UINT SCORE_MUSHROOM = 1000;

class Mushroom: public GameObject
{
public:
	Mushroom(VECTOR2D position);

	void Update(float deltaTime) override;
	void OnCollision(CollisionEvent colEvent) override;
	void Render() override;

private:
	Renderable* GetRenderable() override;
	float _beginY;
	bool _isReady;
	GameObject* _score;
};

