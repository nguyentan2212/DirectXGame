#pragma once
#include "../Core/GameObject.h"

class GUI: public GameObject
{
public:
	GUI();

	void Update(float deltaTime) override;
	void Render() override;

	void IncreaseScore(int score);
	void IncreaseCoin(int coin = 1);
	void UpdateRunSpeed(float speed);
private:
	int _lifePoint = 4;
	int _score = 0;
	int _money = 0;
	int _time = 0;
	float _totalTime = 0;
	float _speed = 0;
};

