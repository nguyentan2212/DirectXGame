#include "Brick.h"
#include "Mushroom.h"
#include "Leaf.h"
#include "../Mario/Mario.h"
#include "../../Graphic/SpriteService.h"
#include "../../Core/Camera.h"
#include "../../Physic/CollisionManager.h"
#include "../../Core/ObjectPool.h"

Brick::Brick(): GameObject(new ObjectState())
{
}

void Brick::Update(float deltaTime)
{
	GameObject::Update(deltaTime);
	if (this->_y > this->_position.y && this->_isTouched)
	{
		this->_position.y = this->_y;
		this->_acceleration = VECTOR2D(0.0f, 0.0f);
		this->_velocity = VECTOR2D(0.0f, 0.0f);

		if (this->_name == "mushroom brick")
		{
			ObjectPool* pool = ObjectPool::GetInstance();
			Mushroom* m = new Mushroom(this->_position + VECTOR2D(0, 16.0f));
			pool->AddGameObject(m);
			this->_renderIndex = 2;
		}
		else if (this->_name == "leaf brick")
		{
			ObjectPool* pool = ObjectPool::GetInstance();
			Leaf* m = new Leaf(this->_position + VECTOR2D(0, 16.0f));
			pool->AddGameObject(m);
			this->_renderIndex = 2;
		}
	}

if (this->_isTouched && this->_name != "mushroom brick" && this->_name != "leaf brick")
{
	// update coin ani
	if (this->_renderIndex == 0)
	{
		if (this->_tempY > 20.0f)
		{
			this->_tempVY += -BRICK_GRAVITY * deltaTime / 1000;
			this->_tempY += this->_tempVY * deltaTime / 1000;
			DebugOut((wchar_t*)L"[INFO] Brick tempY = %f \n", _tempY);
		}
		else
		{
			this->_tempY = 21.0f;
			this->_tempVY = 150.0f;
			this->_renderIndex = 1;
		}
	}
	else if (this->_renderIndex == 1) // update score ani
	{
		if (this->_tempY > 20.0f)
		{
			this->_tempVY += -BRICK_GRAVITY * deltaTime / 1000;
			this->_tempY += this->_tempVY * deltaTime / 1000;
			DebugOut((wchar_t*)L"[INFO] Brick tempY = %f \n", _tempY);
		}
		else
		{
			this->_renderIndex = 2;
		}
	}
}
}

void Brick::Render()
{
	if (this->_isTouched == false)
	{
		GameObject::Render();
		return;
	}
	// draw touched sprite
	SpriteService* sprites = SpriteService::GetInstance();
	Sprite* sprite = sprites->GetSprite("mics52");

	Camera* camera = Camera::GetInstance();
	VECTOR2D cameraPosition = camera->position;

	VECTOR2D worldPosition = GetWorldPosition() - cameraPosition;
	sprite->Draw(worldPosition, this->_isFlipped);

	// draw coin
	if (this->_renderIndex == 0)
	{
		AnimationService* animations = AnimationService::GetInstance();
		Animation* coinAni = animations->GetAnimation("coin");
		coinAni->Render(worldPosition + VECTOR2D(0.0f, this->_tempY));
	}
	else if (this->_renderIndex == 1)
	{
		Sprite* sprite = sprites->GetSprite("hub-and-font/100");
		sprite->Draw(worldPosition + VECTOR2D(0.0f, this->_tempY));
	}

	// render children
	for (GameObject* obj : this->_children)
	{
		obj->Render();
	}
}

Animation* Brick::GetAnimation()
{
	AnimationService* animations = AnimationService::GetInstance();
	return animations->GetAnimation("brick");
}

void Brick::OnCollision(CollisionEvent colEvent)
{
	if (this->_isTouched == false)
	{
		Mario* mario = dynamic_cast<Mario*>(colEvent.collisionObj);
		if (mario != nullptr && colEvent.direction == Direction::DOWN)
		{
			this->_y = this->_position.y;
			this->_acceleration = VECTOR2D(this->_acceleration.x, -BRICK_GRAVITY);
			this->_velocity = VECTOR2D(this->_velocity.x, BRICK_BOUND_SPEED);
			this->_isTouched = true;

			if (this->_name == "mushroom brick")
			{
				this->_renderIndex = 2;
			}
			else
			{
				mario->IncreaseScore(100);
			}
		}

		if (mario != nullptr && (colEvent.direction == Direction::LEFT || colEvent.direction == Direction::RIGHT) && this->_name == "leaf brick")
		{
			this->_y = this->_position.y + 1;
			this->_isTouched = true;
			this->_renderIndex = 2;
		}
	}
}
