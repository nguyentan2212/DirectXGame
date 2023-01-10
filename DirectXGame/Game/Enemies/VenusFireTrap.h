#pragma once
#include "../../Core/GameObject.h"
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

