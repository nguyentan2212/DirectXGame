#pragma once
#include "../../Core/ObjectState.h"

class MarioRunState: public ObjectState
{
public:
	MarioRunState(int direction);
	void OnTransition() override;
	void OnCollision(CollisionEvent colEvent) override;
	void OnKeyDown(int keyCode) override;
	void OnKeyUp(int keyCode) override;
	void OnChangeFigure() override;
	void Update(float deltaTime) override;
private:
	int direction;
};

