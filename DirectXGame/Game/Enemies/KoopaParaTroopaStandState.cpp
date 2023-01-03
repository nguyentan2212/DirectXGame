#include "KoopaParaTroopaStandState.h"
#include "../../Core/GameObject.h"
#include "../Mario/Mario.h"
#include "../Mario/MarioKickState.h"
#include "KoopaParaTroopaRunState.h"

KoopaParaTroopaStandState::KoopaParaTroopaStandState()
{
	this->_name = "stand";
	DebugOut((wchar_t*)L"[INFO] Koopa Paratroopa transition to Stand State \n");
}

void KoopaParaTroopaStandState::OnTransition()
{
	this->_context->width = 16;
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
	Mario* mario = dynamic_cast<Mario*>(colEvent.collisionObj);
	if (mario != nullptr)
	{
		if (colEvent.direction == Direction::LEFT)
		{
			this->_context->TransitionTo(new KoopaParaTroopaRunState(1));
			mario->TransitionTo(new MarioKickState());
		}
		else if (colEvent.direction == Direction::RIGHT)
		{
			this->_context->TransitionTo(new KoopaParaTroopaRunState(-1));
			mario->TransitionTo(new MarioKickState());
		}
	}
}
