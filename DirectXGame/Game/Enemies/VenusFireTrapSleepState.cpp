#include "VenusFireTrapSleepState.h"
#include "../../Core/ObjectPool.h"
#include "../Mario/Mario.h"
#include "VenusFireTrapAttackState.h"

VenusFireTrapSleepState::VenusFireTrapSleepState()
{
	this->_name = "sleep";
	DebugOut((wchar_t*)L"[INFO] Venus Fire Trap transition to Sleep State \n");
}

void VenusFireTrapSleepState::OnTransition()
{
	this->_y = this->_context->GetWorldPosition().y;
}

void VenusFireTrapSleepState::Update(float deltaTime)
{
	VECTOR2D pos = this->_context->GetWorldPosition();
	if (pos.y < _y - this->_context->height)
	{
		pos.y = _y - this->_context->height;
		this->_context->position = pos;
		this->_context->velocity = VECTOR2D(0.0f, 0.0f);
	}

	ObjectPool* pool = ObjectPool::GetInstance();
	GameObject* result = pool->GetGameObjectWithClass("Mario");
	Mario* mario = dynamic_cast<Mario*>(result);
	
	if (mario != nullptr)
	{
		VECTOR2D temp = this->_context->GetWorldPosition() - mario->GetWorldPosition();
		if (abs(temp.x) <= FIRE_TRAP_X_DISTANCE_DETECT)
		{
			Direction direction = temp.x < 0 ? Direction::RIGHT : Direction::LEFT;
			this->_context->TransitionTo(new VenusFireTrapAttackState(direction));
		}
	}
}

void VenusFireTrapSleepState::OnCollision(CollisionEvent colEvent)
{
}
