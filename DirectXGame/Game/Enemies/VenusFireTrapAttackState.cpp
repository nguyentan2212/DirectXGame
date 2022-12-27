#include "VenusFireTrapAttackState.h"
#include "VenusFireTrapSleepState.h"
#include "../../Core/ObjectPool.h"
#include "../Mario/Mario.h"

VenusFireTrapAttackState::VenusFireTrapAttackState(Direction direction)
{
	this->_name = "attack";
	DebugOut((wchar_t*)L"[INFO] Venus Fire Trap transition to Attack State \n");
	this->_direction = direction;
	this->_cooldown = FIRE_TRAP_ATTACK_COOLDOWN;
}

void VenusFireTrapAttackState::OnTransition()
{
	this->_context->velocity = VECTOR2D(0.0f, FIRE_TRAP_Y_SPEED);
	this->_context->direction = this->_direction;
	this->_y = this->_context->GetWorldPosition().y;
}

void VenusFireTrapAttackState::Update(float deltaTime)
{
	VECTOR2D pos = this->_context->GetWorldPosition();
	if (pos.y > _y + this->_context->height)
	{
		pos.y = _y + this->_context->height;
		this->_context->position = pos;
		this->_context->velocity = VECTOR2D(0.0f, 0.0f);
	}

	ObjectPool* pool = ObjectPool::GetInstance();
	GameObject* result = pool->GetGameObjectWithClass("Mario");
	Mario* mario = dynamic_cast<Mario*>(result);

	if (mario != nullptr)
	{
		VECTOR2D temp = this->_context->GetWorldPosition() - mario->GetWorldPosition();
		if (abs(temp.x) > FIRE_TRAP_X_DISTANCE_DETECH)
		{
			this->_context->velocity = VECTOR2D(0.0f, -FIRE_TRAP_Y_SPEED);
			this->_context->TransitionTo(new VenusFireTrapSleepState());
		}
	}

	_cooldown -= deltaTime;
	if (_cooldown < 0)
	{
		_cooldown = FIRE_TRAP_ATTACK_COOLDOWN;
		Attack();
	}
}

void VenusFireTrapAttackState::OnCollision(CollisionEvent colEvent)
{
}

void VenusFireTrapAttackState::Attack()
{
}
