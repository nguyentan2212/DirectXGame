#pragma once
#include "../../Core/GameObject.h"

constexpr float LEAF_GRAVITY = 30;
constexpr float LEAF_Y_SPEED = 70;
constexpr float LEAF_SIZE = 16;

constexpr float LEAF_SCORE_SPEED = 20;
constexpr float LEAF_SCORE_MAX_LENGHT = 80;
constexpr UINT SCORE_LEAF = 1000;

class Leaf : public GameObject
{
public:
	Leaf(VECTOR2D pos);

	void Update(float deltaTime) override;
	void OnCollision(CollisionEvent colEvent) override;
	void Render() override;

private:
	Renderable* GetRenderable() override;
	GameObject* _score;
};

