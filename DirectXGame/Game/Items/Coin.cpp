#include "Coin.h"
#include "../../Graphic/SpriteService.h"
#include "../../Graphic/AnimationService.h"
#include "../../Physic/CollisionManager.h"
#include "../../Core/ObjectPool.h"

Coin::Coin(VECTOR2D position): GameObject(new ObjectState())
{
	this->_name = "coin";
	this->_position = position;
	this->_width = COIN_SIZE;
	this->_height = COIN_SIZE;
	this->_position = position;
	this->_score = nullptr;
}

void Coin::Update(float deltaTime)
{
	if (this->_isActive == false)
	{
		return;
	}

	if (this->_score != nullptr)
	{
		this->_score->Update(deltaTime);
	}

	if (this->_score != nullptr && this->_score->isActive && this->_score->position.y > this->_position.y + SCORE_MAX_LENGHT)
	{
		this->_score->isActive = false;
		this->isActive = false;
	}

	CollisionManager::Processing(this, deltaTime);
	GameObject::Update(deltaTime);
}

void Coin::OnCollision(CollisionEvent colEvent)
{
	if (this->_score != nullptr && colEvent.collisionObj->name == "brick" && colEvent.direction == Direction::DOWN)
	{
		this->_velocity = VECTOR2D(0.0f, 0.0f);
		this->_acceleration = VECTOR2D(0.0f, 0.0f);
		this->_score->isActive = true;
	}
}

Coin* Coin::ScoreCoin(VECTOR2D position)
{
	Coin* pCoin = new Coin(position);

	pCoin->_velocity = VECTOR2D(0.0f, COIN_SPEED);
	pCoin->_acceleration = VECTOR2D(0.0f, -COIN_GRAVITY);

	ObjectPool* pool = ObjectPool::GetInstance();
	SpriteService* sprites = SpriteService::GetInstance();
	pCoin->_score = new GameObject(sprites->GetSprite("hub-and-font/100"));
	pCoin->_score->position = position + VECTOR2D(0.0f, COIN_SIZE);
	pCoin->_score->velocity = VECTOR2D(0.0f, SCORE_SPEED);
	pCoin->_score->isActive = false;
	pool->AddGameObject(pCoin->_score);

	return pCoin;
}

Renderable* Coin::GetRenderable()
{
	if (this->_score != nullptr && this->_score->isActive)
	{
		return nullptr;
	}

	AnimationService* animations = AnimationService::GetInstance();
	return animations->GetAnimation("coin");
}
