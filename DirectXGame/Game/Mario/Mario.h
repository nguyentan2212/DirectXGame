#pragma once
#include <dinput.h>
#include "../../Core/GameObject.h"

constexpr float SPEED = 100;
class Mario: public GameObject
{
public:
	Mario();

	void Update(float deltaTime) override;
	void Render() override;

	void OnKeyDown(int keyCode) override;
	void OnKeyUp(int keyCode) override;
	void OnCollision(CollisionEvent colEvent) override;

private:
	bool _isGrounded = false;
};

