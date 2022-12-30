#include "VenusFireTrapAttackState.h"
#include "VenusFireTrapSleepState.h"
#include "FireBall.h"
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

	_cooldown -= deltaTime;
	//DebugOut((wchar_t*)L"[INFO] Venus Fire Trap cooldown %f, delta time %f \n", _cooldown, deltaTime);

	if (mario != nullptr)
	{
		if (_cooldown < 0)
		{
			Attack(mario->GetWorldPosition());
		}

		VECTOR2D temp = this->_context->GetWorldPosition() - mario->GetWorldPosition();
		Direction direction = temp.x < 0 ? Direction::RIGHT : Direction::LEFT;
		if (this->_context->direction != direction)
		{
			this->_context->direction = direction;
		}

		if (abs(temp.x) > FIRE_TRAP_X_DISTANCE_DETECH)
		{
			this->_context->velocity = VECTOR2D(0.0f, -FIRE_TRAP_Y_SPEED);
			this->_context->TransitionTo(new VenusFireTrapSleepState());
		}
	}
}

void VenusFireTrapAttackState::OnCollision(CollisionEvent colEvent)
{
}

void VenusFireTrapAttackState::Attack(VECTOR2D target)
{
	VECTOR2D pos = this->_context->GetWorldPosition() + VECTOR2D(0.0f, 10.0f);
	FireBall* fire = new FireBall(pos, FIRE_BALL_MAX_DISTANCE);
	VECTOR2D v = target - pos;
	D3DXVec2Normalize(&v, &v);
	fire->velocity = v * FIRE_BALL_SPEED;
	ObjectPool* pool = ObjectPool::GetInstance();
	pool->AddGameObject(fire);
	_cooldown = FIRE_TRAP_ATTACK_COOLDOWN;
	DebugOut((wchar_t*)L"[INFO] Venus Fire Trap fired \n");
}
