#pragma once
#include "../../Core/GameObject.h"

class FireBall: public GameObject
{
public:
	FireBall(VECTOR2D begin, float maxLength);

	void Update(float deltaTime) override;
	void Render() override;
	void OnCollision(CollisionEvent colEvent) override;
private:
	VECTOR2D _begin;
	float _maxLength;

	Animation* GetAnimation() override;
};

