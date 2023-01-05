#pragma once
#include "../../Core/GameObject.h"

class ParaGoomba: public GameObject
{
public:
	ParaGoomba();

	void Render() override;
	void Update(float deltaTime) override;
	void OnCollision(CollisionEvent colEvent) override;
	
	bool isLostWings = false;
	bool isDeath = false;
private:
	Animation* GetAnimation() override;
	float _tempY;
	Sprite* _lostWingScore = nullptr;
	Sprite* _deathScore = nullptr;

	void IsAttacked();
};

