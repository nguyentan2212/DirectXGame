#include "VenusFireTrap.h"
#include "../../Core/GameObject.h"
#include "../../Core/ObjectPool.h"
#include "FireBall.h"

VenusFireTrap::VenusFireTrap(VECTOR2D sleepPos, string name): GameObject()
{
	this->_name = name;
	this->_width = FIRE_TRAP_WIDTH;
	this->_height = FIRE_TRAP_HEIGHT;
	this->_sleepPosition = sleepPos;
	SetState(FIRE_TRAP_SLEEP);
}

void VenusFireTrap::Update(float deltaTime)
{
	if (this->_isActive == false)
	{
		return;
	}
	if (this->_attackTarget == nullptr)
	{
		ObjectPool* pool = ObjectPool::GetInstance();
		this->_attackTarget = pool->GetGameObjectWithName("mario");
	}
	
	switch (GetState())
	{
	case FIRE_TRAP_SLEEP:
		if (this->position.y <= this->_sleepPosition.y)
		{
			this->_velocity = VECTOR2D(0.0f, 0.0f);
			this->position = this->_sleepPosition;
		}
		if (DetectTarget() && this->velocity.y == 0)
		{
			SetState(FIRE_TRAP_AWAKE);
		}
		break;
	case FIRE_TRAP_AWAKE:
		if (this->_sleepPosition.y + FIRE_TRAP_HEIGHT <= this->position.y)
		{
			SetState(FIRE_TRAP_ATTACK);
			this->_velocity = VECTOR2D(0.0f, 0.0f);
			this->position = this->_sleepPosition + VECTOR2D(0.0f, FIRE_TRAP_HEIGHT);
		}
		break;
	case FIRE_TRAP_ATTACK:
		if (DetectTarget() == false)
		{
			SetState(FIRE_TRAP_SLEEP);
		}
		else
		{
			this->_cooldown -= deltaTime;
			if (this->_cooldown <= 0)
			{
				this->_cooldown = FIRE_TRAP_ATTACK_COOLDOWN;
				Attack();
			}
		}
		break;
	default:
		break;
	}

	VECTOR2D temp = this->position - this->_attackTarget->position;
	this->direction = temp.x < 0 ? Direction::RIGHT : Direction::LEFT;
	GameObject::Update(deltaTime);
	//DebugOut((wchar_t*)L"[INFO] Venus Fire Trap vel x = %f, y = %f \n", this->position.x, this->position.y);
}

void VenusFireTrap::Render()
{
	_isFlipped = this->_direction == DIRECTION::LEFT ? false : true;
	GameObject::Render(0.4f);
}

void VenusFireTrap::OnCollision(CollisionEvent colEvent)
{
}

void VenusFireTrap::SetState(UINT stateValue, string stateName)
{
	if (stateValue == GetState())
	{
		return;
	}
	switch (stateValue)
	{
	case FIRE_TRAP_SLEEP:
		if (GetState() != FIRE_TRAP_ATTACK)
		{
			return;
		}
		Sleep();
		break;
	case FIRE_TRAP_AWAKE:
		Awake();
		break;
	case FIRE_TRAP_ATTACK:
		if (GetState() != FIRE_TRAP_AWAKE)
		{
			return;
		}
		break;
	default:
		return;
	}
	this->_states[stateName] = stateValue;
}

Renderable* VenusFireTrap::GetRenderable()
{
	string aniName = this->_name + " ";
	AnimationService* animations = AnimationService::GetInstance();

	if (GetState() == FIRE_TRAP_SLEEP)
	{
		aniName += "sleep";
	}
	else
	{
		if (this->position.y < this->_attackTarget->position.y)
		{
			aniName += "attack up";
		}
		else
		{
			aniName += "attack down";
		}
	}

	return animations->GetAnimation(aniName);
}

bool VenusFireTrap::DetectTarget()
{
	if (this->_attackTarget == nullptr)
	{
		return false;
	}

	VECTOR2D temp = this->position - this->_attackTarget->position;
	if (abs(temp.x) <= FIRE_TRAP_X_DISTANCE_DETECT)
	{
		return true;
	}
	return false;
}

void VenusFireTrap::Sleep()
{
	this->_velocity = VECTOR2D(0.0f, -FIRE_TRAP_Y_SPEED);
}

void VenusFireTrap::Attack()
{
	VECTOR2D pos = this->position + VECTOR2D(0.0f, FIRE_TRAP_HEIGHT * 0.5f);

	FireBall* fire = new FireBall(pos, FIRE_BALL_MAX_DISTANCE);
	VECTOR2D v = this->_attackTarget->position - pos;
	D3DXVec2Normalize(&v, &v);
	fire->velocity = v * FIRE_BALL_SPEED;

	ObjectPool* pool = ObjectPool::GetInstance();
	pool->AddGameObject(fire);

	DebugOut((wchar_t*)L"[INFO] Venus Fire Trap attacked \n");
}

void VenusFireTrap::Awake()
{
	this->_velocity = VECTOR2D(0.0f, FIRE_TRAP_Y_SPEED);
}
