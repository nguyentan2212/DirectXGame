#include "VenusFireTrapAttackState.h"
#include "VenusFireTrapSleepState.h"
#include "FireBall.h"
#include "../../Core/ObjectPool.h"

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
	_cooldown -= deltaTime;

	VECTOR2D pos = this->_context->GetWorldPosition();
	if (pos.y > _y + this->_context->height)
	{
		pos.y = _y + this->_context->height;
		this->_context->position = pos;
		this->_context->velocity = VECTOR2D(0.0f, 0.0f);
	}

	ObjectPool* pool = ObjectPool::GetInstance();
	GameObject* obj = pool->GetGameObjectWithName("mario");

	if (obj != nullptr)
	{
		if (_cooldown < 0)
		{
			Attack(obj->GetWorldPosition());
		}

		VECTOR2D temp = this->_context->GetWorldPosition() - obj->GetWorldPosition();
		Direction direction = temp.x < 0 ? Direction::RIGHT : Direction::LEFT;
		if (this->_context->direction != direction)
		{
			this->_context->direction = direction;
		}

		if (abs(temp.x) > FIRE_TRAP_X_DISTANCE_DETECT)
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
	_cooldown = FIRE_TRAP_ATTACK_COOLDOWN;

	VECTOR2D pos = this->_context->GetWorldPosition() + VECTOR2D(0.0f, 10.0f);
	FireBall* fire = new FireBall(pos, FIRE_BALL_MAX_DISTANCE);
	VECTOR2D v = target - pos;
	D3DXVec2Normalize(&v, &v);
	fire->velocity = v * FIRE_BALL_SPEED;

	ObjectPool* pool = ObjectPool::GetInstance();
	pool->AddGameObject(fire);
	
	DebugOut((wchar_t*)L"[INFO] Venus Fire Trap fired \n");
}
