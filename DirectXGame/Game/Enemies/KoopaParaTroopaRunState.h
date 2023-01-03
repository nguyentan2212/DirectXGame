#pragma once
#include "../../Core/ObjectState.h"

constexpr float KOOPA_PARATROOPA_RUN_SPEED_X = 65;
constexpr float KOOPA_PARATROOPA_GRAVITY = 120;

class KoopaParaTroopaRunState: public ObjectState
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

