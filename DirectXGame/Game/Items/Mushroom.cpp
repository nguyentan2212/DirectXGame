#include "Mushroom.h"
#include "../Mario/Mario.h"
#include "../../Graphic/SpriteService.h"
#include "../../Core/Camera.h"
#include "../../Physic/CollisionManager.h"
#include "../Mario/MarioChangeFigureState.h"

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
	/*CollisionManager* collision = CollisionManager::GetInstance();
	list<GameObject*> results = collision->RayCastWith(this, DIRECTION::DOWN, 5.0f, deltaTime);
	for (GameObject* obj : results)
	{
		if (obj->name == "ground" || obj->name == "panel" || obj->name == "pine")
		{
			isGrounded = true;
		}
	}*/
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
		if (this->_tempY <= 100.0f)
		{
			this->_tempY += MUSHROOM_X_SPEED * deltaTime / 1000;
			DebugOut((wchar_t*)L"[INFO] Brick tempY = %f \n", _tempY);
		}
		else
		{
			this->_renderIndex = 2;
			this->_isActive = false;
		}
	}
	GameObject::Update(deltaTime);
	DebugOut((wchar_t*)L"[INFO] Mushroom world y = %f \n", this->GetWorldPosition().y);
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
	sprite->Render(worldPosition, this->_isFlipped);
}

void Mushroom::OnCollision(CollisionEvent colEvent)
{
	string n = colEvent.collisionObj->name;
	if ((n == "pine" || n == "ground" || n == "panel"))
	{
		this->_position += this->_velocity * colEvent.entryTime;
		if (colEvent.direction == Direction::DOWN)
		{
			this->_velocity = VECTOR2D(this->_velocity.x, 0.0f);
			this->_acceleration = VECTOR2D(0.0f, 0.0f);
		}
		else if ((colEvent.direction == Direction::LEFT || colEvent.direction == Direction::RIGHT) && (n == "pine" || n == "ground"))
		{
			this->_velocity = VECTOR2D(-this->_velocity.x, 0.0f);
		}
	}
	Mario* mario = dynamic_cast<Mario*>(colEvent.collisionObj);
	if (mario != nullptr)
	{
		this->_renderIndex = 1;
		this->_velocity = VECTOR2D(0.0f, 0.0f);
		this->_acceleration = VECTOR2D(0.0f, 0.0f);
		mario->IncreaseScore(1000);
		mario->TransitionTo(new MarioChangeFigureState("super mario"));
	}
	
}
