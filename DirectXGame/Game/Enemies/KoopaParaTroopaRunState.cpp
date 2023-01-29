#include "KoopaParaTroopaRunState.h"
#include "../../Core/GameObject.h"
#include "KoopaParaTroopa.h"

KoopaParaTroopaRunState::KoopaParaTroopaRunState(int direction)
{
	this->_name = "run";
	this->_direction = direction;
	this->_isGrounded = true;
	DebugOut((wchar_t*)L"[INFO] Koopa Paratroopa transition to Run State \n");
}

void KoopaParaTroopaRunState::OnTransition()
{
	this->_context->height = 16;
	this->_context->velocity = VECTOR2D(KOOPA_PARATROOPA_RUN_SPEED_X * this->_direction, 0.0f);
	this->_context->acceleration = VECTOR2D(0.0f, 0.0f);
}

void KoopaParaTroopaRunState::Update(float deltaTime)
{
	
}

void KoopaParaTroopaRunState::OnCollision(CollisionEvent colEvent)
{
	
}
