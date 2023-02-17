#pragma once
#include "../Core/GameObject.h"

constexpr float MAP_MARIO_SPEED = 20;
constexpr float PORTAL_SIZE = 16;

class MapMario: public GameObject
{
public:
	MapMario();
	void Update(float deltaTime) override;
	void OnKeyDown(int keyCode) override;
	void OnKeyUp(int keyCode) override;
	void OnCollision(CollisionEvent colEvent) override;

	bool canTeleport = false;

private:
	VECTOR2D _portalPosition;
};

