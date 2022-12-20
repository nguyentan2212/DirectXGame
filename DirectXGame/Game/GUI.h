#pragma once
#include "../Core/GameObject.h"

class GUI: public GameObject
{
public:
	GUI();

	void Update(float deltaTime) override;
	void Render() override;
private:
	int _lifePoint = 4;
	int _score = 4700;
	int _money = 58;
	int _time = 0;
	float _totalTime = 0;
};

