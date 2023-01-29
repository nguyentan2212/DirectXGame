#pragma once
#include "../../Core/GameObject.h"

class Head: public GameObject
{
public:
	Head(float width, float height);

	void Update(float deltaTime) override;
	void OnCollision(CollisionEvent colEvent) override;
	void Render() override;

	GameObject* body = nullptr;

	void SetGravity(float gravity);

private:
	float _gravity;
};

