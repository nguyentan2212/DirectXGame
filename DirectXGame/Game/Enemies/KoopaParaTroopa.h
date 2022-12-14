#pragma once
#include "../../Core/GameObject.h"

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
};

