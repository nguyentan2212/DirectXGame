#pragma once
#include "../../Core/State.h"

class KoopaParaTroopaRunState: public State
{
public:
	KoopaParaTroopaRunState(int direction);

	void OnTransition() override;
	void Update(float deltaTime) override;
	void OnCollision(CollisionEvent colEvent) override;

private:
	int _direction;
	bool _isGrounded;
};

