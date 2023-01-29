#include "KoopaParaTroopaStandState.h"
#include "../../Core/GameObject.h"

KoopaParaTroopaStandState::KoopaParaTroopaStandState()
{
	this->_name = "stand";
	DebugOut((wchar_t*)L"[INFO] Koopa Paratroopa transition to Stand State \n");
}

void KoopaParaTroopaStandState::OnTransition()
{
	this->_context->height = 16;
	this->_context->velocity = VECTOR2D(0.0f, 0.0f);
	this->_context->acceleration = VECTOR2D(0.0f, 0.0f);
	VECTOR2D pos = this->_context->GetWorldPosition();
	pos.y -= 5.0f;
	this->_context->position = pos;
}

void KoopaParaTroopaStandState::Update(float deltaTime)
{
}

void KoopaParaTroopaStandState::OnCollision(CollisionEvent colEvent)
{
	
}
