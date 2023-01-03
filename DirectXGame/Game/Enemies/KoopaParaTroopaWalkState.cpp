#include "KoopaParaTroopaWalkState.h"
#include "../../Core/GameObject.h"
#include "../Mario/Mario.h"
#include "../Mario/MarioJumpState.h"
#include "../Mario/MarioChangeFigureState.h"
#include "../Mario/MarioDeathState.h"
#include "KoopaParaTroopaStandState.h"

KoopaParaTroopaWalkState::KoopaParaTroopaWalkState()
{
	this->_name = "walk";
	DebugOut((wchar_t*)L"[INFO] Koopa Paratroopa transition to Walk State \n");
}

void KoopaParaTroopaWalkState::OnTransition()
{
	this->_context->width = 16;
	this->_context->height = 26;
	this->_context->velocity = VECTOR2D(-KOOPA_PARATROOPA_WALK_SPEED_X, 0.0f);
	this->_context->acceleration = VECTOR2D(0.0f, 0.0f);
}

void KoopaParaTroopaWalkState::OnCollision(CollisionEvent colEvent)
{
	if (colEvent.collisionObj->name == "border")
	{
		VECTOR2D v = this->_context->velocity;
		v.x *= -1;
		this->_context->velocity = v;
	}
	else 
	{
		Mario* mario = dynamic_cast<Mario*>(colEvent.collisionObj);
		if (mario != nullptr)
		{
			if (colEvent.direction == Direction::UP)
			{
				this->_context->TransitionTo(new KoopaParaTroopaStandState());
				mario->TransitionTo(new MarioJumpState());
			}
			else
			{
				string stateName = mario->GetStateName();
				if (mario->name != "small mario" && stateName.find("change figure") == string::npos)
				{
					mario->TransitionTo(new MarioChangeFigureState("small mario"));
				}
				else if (stateName.find("change figure") == string::npos && stateName != "death")
				{
					mario->TransitionTo(new MarioDeathState());
				}
			}
		}
	}
}
