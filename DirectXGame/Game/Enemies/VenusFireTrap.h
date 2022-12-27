#pragma once
#include "../../Core/GameObject.h"
class VenusFireTrap: public GameObject
{
public:
	VenusFireTrap();

	void Update(float deltaTime) override;
	void Render() override;
	void OnCollision(CollisionEvent colEvent) override;

private:
	Animation* GetAnimation() override;
};

