#include "Mushroom.h"
#include "../Mario/Mario.h"
#include "../../Graphic/SpriteService.h"
#include "../../Core/Camera.h"
#include "../../Physic/CollisionManager.h"

Mushroom::Mushroom(VECTOR2D pos): GameObject(new ObjectState())
{
	this->position = pos;
	this->_height = 16.0f;
	this->_width = 16.0f;
	this->_velocity = VECTOR2D(MUSHROOM_X_SPEED, 0.0f);
}

void Mushroom::Update(float deltaTime)
{
	if (this->_isActive == false)
	{
		return;
	}

	bool isGrounded = false;
	CollisionManager* collision = CollisionManager::GetInstance();
	list<GameObject*> results = collision->RayCastWith(this, DIRECTION::DOWN, 5.0f, deltaTime);
	for (GameObject* obj : results)
	{
		if (obj->name == "ground" || obj->name == "panel" || obj->name == "pine")
		{
			isGrounded = true;
		}
	}
	if (isGrounded == false)
	{
		this->_acceleration = VECTOR2D(0.0f, -MUSHROOM_GRAVITY);
	}
	else
	{
		this->_acceleration = VECTOR2D(0.0f, 0.0f);
	}

	// update score animation
	if (this->_renderIndex == 1)
	{
		if (this->_tempY > 20.0f)
		{
			this->_tempVY += -MUSHROOM_GRAVITY * deltaTime / 1000;
			this->_tempY += this->_tempVY * deltaTime / 1000;
			DebugOut((wchar_t*)L"[INFO] Brick tempY = %f \n", _tempY);
		}
		else
		{
			this->_renderIndex = 2;
			this->_isActive = false;
		}
	}
	

	GameObject::Update(deltaTime);
}

void Mushroom::Render()
{
	if (this->_isActive == false)
	{
		return;
	}
	Camera* camera = Camera::GetInstance();
	VECTOR2D cameraPosition = camera->position;
	VECTOR2D worldPosition = GetWorldPosition() - cameraPosition;

	SpriteService* sprites = SpriteService::GetInstance();
	Sprite* sprite = sprites->GetSprite("mics107");
	
	if (this->_renderIndex == 1)
	{
		sprite = sprites->GetSprite("hub-and-font/1000");
		worldPosition = worldPosition + VECTOR2D(0.0f, this->_tempY);
	}
	sprite->Draw(worldPosition, this->_isFlipped);
}

void Mushroom::OnCollision(CollisionEvent colEvent)
{
	string n = colEvent.collisionObj->name;
	if ((n == "pine" || n == "ground" || n == "panel") && colEvent.direction == Direction::DOWN)
	{
		this->_position += this->_velocity * colEvent.entryTimePercent * colEvent.deltaTime / 1000;
		this->_velocity = VECTOR2D(this->_velocity.x, 0.0f);
		this->_acceleration = VECTOR2D(0.0f, 0.0f);
	}
	Mario* mario = dynamic_cast<Mario*>(colEvent.collisionObj);
	if (mario != nullptr)
	{
		this->_renderIndex = 1;
		mario->IncreaseScore(1000);
	}
	
}
