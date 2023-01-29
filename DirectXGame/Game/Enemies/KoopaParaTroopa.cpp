#include "KoopaParaTroopa.h"
#include "KoopaParaTroopaWalkState.h"
#include "KoopaParaTroopaStandState.h"
#include "../../Graphic/SpriteService.h"
#include "../../Physic/CollisionManager.h"
#include "../../Core/ObjectPool.h"

KoopaParaTroopa::KoopaParaTroopa(): GameObject(new KoopaParaTroopaWalkState())
{
	this->_name = "koopa paratroopa";
	this->_width = KOOPA_PARATROOPA_WIDTH;
	this->_height = KOOPA_PARATROOPA_HEIGHT;
	this->_head = new Head(KOOPA_PARATROOPA_WIDTH / 2.0f, KOOPA_PARATROOPA_HEIGHT);
	this->_head->body = this;
	this->_head->SetGravity(KOOPA_PARATROOPA_GRAVITY);
	ObjectPool* pool = ObjectPool::GetInstance();
	pool->AddGameObject(this->_head);
}

void KoopaParaTroopa::Update(float deltaTime)
{
	this->_acceleration = VECTOR2D(0.0f, -KOOPA_PARATROOPA_GRAVITY);
	this->_velocity += this->_acceleration * deltaTime / 1000;

	this->_isGrounded = false;
	CollisionManager::Processing(this, deltaTime);
	this->_state->Update(deltaTime);
	GameObject::Update(deltaTime);
	if (this->_velocity.x < 0)
	{
		this->_direction = DIRECTION::LEFT;
	}
	else if (this->_velocity.x > 0)
	{
		this->_direction = DIRECTION::RIGHT;
	}
	//DebugOut((wchar_t*)L"[INFO] Koopa x: %f \n", this->_position.x);
}

void KoopaParaTroopa::Render()
{
	_isFlipped = this->_direction == DIRECTION::LEFT ? false : true;
	GameObject::Render();
}

void KoopaParaTroopa::OnCollision(CollisionEvent colEvent)
{
	string objName = colEvent.collisionObj->name;
	if (objName == "ground" || objName == "cloud" || objName == "panel")
	{
		if (colEvent.direction == Direction::DOWN)
		{
			this->_isGrounded = true;
			this->_position += this->_velocity * colEvent.entryTime;
			this->_velocity = VECTOR2D(this->_velocity.x, 0);
			this->_acceleration = VECTOR2D(this->_acceleration.x, 0.0f);
		}
	}
}

Renderable* KoopaParaTroopa::GetRenderable()
{
	AnimationService* anis = AnimationService::GetInstance();
	string stateName = this->_state->name;
	return anis->GetAnimation("koopa paratroopa " + stateName);
}
