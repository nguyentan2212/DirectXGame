#include "KoopaParaTroopaWalkState.h"
#include "../../Core/GameObject.h"
#include "KoopaParaTroopa.h"

KoopaParaTroopaWalkState::KoopaParaTroopaWalkState()
{
	this->_name = "walk";
	DebugOut((wchar_t*)L"[INFO] Koopa Paratroopa transition to Walk State \n");
}

void KoopaParaTroopaWalkState::OnTransition()
{
	this->_context->velocity = VECTOR2D(-KOOPA_PARATROOPA_WALK_SPEED_X, 0.0f);
	this->_context->acceleration = VECTOR2D(0.0f, 0.0f);
}

void KoopaParaTroopaWalkState::OnCollision(CollisionEvent colEvent)
{
	
}
