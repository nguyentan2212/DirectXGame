#pragma once
#include "../Core/GameObject.h"

constexpr float DISTANCE = 32;
constexpr float SPEED = 10;

class MapMonster: public GameObject
{
public:
	MapMonster(VECTOR2D pos);
	void Update(float deltaTime) override;

private:
	float _distance = 0;
	VECTOR2D _firstPos;
};

