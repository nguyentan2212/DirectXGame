#pragma once
#include "../../Core/GameObject.h"

constexpr float FIRE_TRAP_WIDTH = 16;
constexpr float FIRE_TRAP_HEIGHT = 32;

class VenusFireTrap: public GameObject
{
public:
	VenusFireTrap();

	void Render() override;
	void Update(float deltaTime) override;
	void OnCollision(CollisionEvent colEvent) override;

private:
	Renderable* GetRenderable() override;
};

