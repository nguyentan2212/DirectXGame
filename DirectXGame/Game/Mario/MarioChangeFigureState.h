#pragma once
#include "../../Core/State.h"
class MarioChangeFigureState: public State
{
public:
	MarioChangeFigureState(string newFigure);
	void OnTransition() override;
	void Update(float deltaTime) override;

private:
	string _newFigure;
	float _coolDown = 1000.0f;
};

