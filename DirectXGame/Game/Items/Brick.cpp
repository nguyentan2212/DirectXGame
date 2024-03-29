#include "Brick.h"
#include "Coin.h"
#include "Mushroom.h"
#include "Leaf.h"
#include "../../Graphic/SpriteService.h"
#include "../../Graphic/AnimationService.h"
#include "../../Physic/CollisionManager.h"
#include "../Mario/Mario.h"
#include "../../Core/ObjectPool.h"

Brick::Brick(GameObject* content, VECTOR2D position): GameObject()
{
	this->_position = position;
	this->_beginY = position.y;
	this->_name = "brick";
	this->_height = BRICK_SIZE;
	this->_width = BRICK_SIZE;
	SetState(BRICK_UNTOUCHED);
	this->_content = content;
	this->_content->isActive = false;
}

void Brick::Update(float deltaTime)
{
	if (this->_isActive == false)
	{
		return;
	}

	this->_content->Update(deltaTime);
	CollisionManager::Processing(this, deltaTime);
	GameObject::Update(deltaTime);

	if (this->_name == "soft brick" && GetState() == BRICK_TOUCHED)
	{
		this->_content->position = this->position;
		this->_content->isActive = true;
		this->_isBlocking = true;

		ObjectPool* pool = ObjectPool::GetInstance();
		Mario* mario = dynamic_cast<Mario*>(pool->GetGameObjectWithClass("Mario"));
		CollisionEvent e = CollisionManager::CalcAABB(this->_content, mario, deltaTime);
		if (e.direction != DIRECTION::NONE)
		{
			SetState(BRICK_TOUCHED_TWICE);
			this->_content->isActive = false;
			mario->IncreaseCoin();
		}
	}

	if (this->_name == "soft brick btn" && GetState() == BRICK_TOUCHED)
	{
		this->_content->position = this->position + VECTOR2D(0.0f, 16.0f);
		
		ObjectPool* pool = ObjectPool::GetInstance();
		Mario* mario = dynamic_cast<Mario*>(pool->GetGameObjectWithClass("Mario"));
		CollisionEvent e = CollisionManager::CalcAABB(this->_content, mario, deltaTime);
		if (e.direction != DIRECTION::NONE)
		{
			SpriteService* sprites = SpriteService::GetInstance();
			SetState(BRICK_TOUCHED_TWICE);
			this->_content->SetRenderable(sprites->GetSprite("mics123"));
			vector<GameObject*> objs = pool->GetAllGameObject(true);
			for (GameObject* obj : objs)
			{
				if (obj->name == "soft brick")
				{
					obj->SetState(BRICK_TOUCHED);
					
				}
			}
		}
	}
	if (this->_position.y < this->_beginY && GetState() == BRICK_TOUCHED)
	{
		this->_position = VECTOR2D(this->_position.x, this->_beginY);
		this->_velocity = VECTOR2D(0.0f, 0.0f);
		this->_acceleration = VECTOR2D(0.0f, 0.0f);
		if (this->_content->name == "mushroom" || this->_content->name == "leaf")
		{
			this->_content->isActive = true;
		}
	}
}

Renderable* Brick::GetRenderable()
{
	AnimationService* animations = AnimationService::GetInstance();
	SpriteService* sprites = SpriteService::GetInstance();

	if (this->name == "soft brick" && (GetState() == BRICK_TOUCHED || GetState() == BRICK_TOUCHED_TWICE))
	{
		return nullptr;
	}

	if (GetState() == BRICK_TOUCHED || GetState() == BRICK_TOUCHED_TWICE)
	{
		return sprites->GetSprite("mics52");
	}

	if (this->name == "soft brick" || this->name == "soft brick btn")
	{
		return animations->GetAnimation("soft brick");
	}
	return animations->GetAnimation("brick");
}

void Brick::OnCollision(CollisionEvent colEvent)
{
	string className = typeid(*colEvent.collisionObj).name();

	if (className == "class Mario" && this->name != "soft brick" && this->name != "soft brick btn" && colEvent.direction == Direction::DOWN &&
		GetState() == BRICK_UNTOUCHED && colEvent.collisionObj->GetState("brick") == 0)
	{
		this->_velocity = VECTOR2D(0.0f, BRICK_BOUND_SPEED);
		this->_acceleration = VECTOR2D(0.0f, -BRICK_GRAVITY);
		SetState(BRICK_TOUCHED);
		colEvent.collisionObj->SetState(1, "brick");
		Mario* mario = dynamic_cast<Mario*>(colEvent.collisionObj);
		mario->IncreaseScore(SCORE_COIN_BRICK);
		if (this->_content->name == "score coin")
		{
			this->_content->isActive = true;
		}
	}
	else if (className == "class Mario" && this->name == "soft brick btn" && colEvent.direction == Direction::DOWN)
	{
		this->_content->isActive = true;
		SetState(BRICK_TOUCHED);
	}
	else if (className == "class KoopaParaTroopa" && GetState() == BRICK_UNTOUCHED &&
		(colEvent.direction == Direction::LEFT || colEvent.direction == Direction::RIGHT))
	{
		if (this->_content->name == "leaf")
		{
			SetState(BRICK_TOUCHED);
			this->_content->isActive = true;
		}
	}
}

void Brick::Render()
{
	if (this->_isActive == false)
	{
		return;
	}
	if (this->_content != nullptr && this->_content->isActive == true)
	{
		this->_content->Render();
	}
	GameObject::Render();
}

Brick* Brick::CreateCoinBrick(VECTOR2D position)
{
	return new Brick(Coin::ScoreCoin(position), position);
}

Brick* Brick::CreateMushroomBrick(VECTOR2D position)
{
	Brick* obj = new Brick(new Mushroom(position), position);
	obj->name = "mushroom brick";
	return obj;
}

Brick* Brick::CreateLeafBrick(VECTOR2D position)
{
	Brick* obj = new Brick(new Leaf(position), position);
	obj->name = "leaf brick";
	return obj;
}

Brick* Brick::CreateSoftBrick(VECTOR2D position)
{
	Brick* obj = new Brick(new Coin(position), position);
	obj->name = "soft brick";
	return obj;
}

Brick* Brick::CreateSoftBrickWithButton(VECTOR2D position)
{
	AnimationService* animations = AnimationService::GetInstance();
	Brick* obj = new Brick(new GameObject(animations->GetAnimation("soft brick btn")), position);
	obj->name = "soft brick btn";
	obj->width = 16;
	obj->height = 16;
	return obj;
}
