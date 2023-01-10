#include "Leaf.h"
#include "../Mario/Mario.h"
#include "../../Graphic/SpriteService.h"
#include "../../Core/Camera.h"
#include "../../Physic/CollisionManager.h"
#include "../Mario/MarioChangeFigureState.h"

Leaf::Leaf(VECTOR2D pos): GameObject(new ObjectState())
{
	this->position = pos;
	this->_height = 16.0f;
	this->_width = 16.0f;
	this->_velocity = VECTOR2D(0.0f, LEAF_Y_SPEED);
	this->_acceleration = VECTOR2D(0.0F, -LEAF_GRAVITY);
}

void Leaf::Update(float deltaTime)
{
	if (this->_isActive == false)
	{
		return;
	}

	if (GetWorldPosition().y <= -40)
	{
		this->_isActive = false;
		return;
	}

	if (this->_renderIndex == 1)
	{
		if (this->_tempY <= 100.0f)
		{
			this->_tempY += LEAF_Y_SPEED / 3 * deltaTime / 1000;
			//DebugOut((wchar_t*)L"[INFO] Brick tempY = %f \n", _tempY);
		}
		else
		{
			this->_renderIndex = 2;
			this->_isActive = false;
		}
	}

	GameObject::Update(deltaTime);
	//DebugOut((wchar_t*)L"[INFO] Leaf world y = %f \n", this->GetWorldPosition().y);
}

void Leaf::Render()
{
	if (this->_isActive == false)
	{
		return;
	}
	Camera* camera = Camera::GetInstance();
	VECTOR2D cameraPosition = camera->position;
	VECTOR2D worldPosition = GetWorldPosition() - cameraPosition;

	SpriteService* sprites = SpriteService::GetInstance();
	Sprite* sprite = sprites->GetSprite("mics114");

	if (this->_renderIndex == 1)
	{
		sprite = sprites->GetSprite("hub-and-font/1000");
		worldPosition = worldPosition + VECTOR2D(0.0f, this->_tempY);
	}
	sprite->Render(worldPosition, this->_isFlipped);
}

void Leaf::OnCollision(CollisionEvent colEvent)
{
	Mario* mario = dynamic_cast<Mario*>(colEvent.collisionObj);
	if (mario != nullptr)
	{
		this->_renderIndex = 1;
		this->_velocity = VECTOR2D(0.0f, 0.0f);
		this->_acceleration = VECTOR2D(0.0f, 0.0f);
		mario->IncreaseScore(1000);
		mario->TransitionTo(new MarioChangeFigureState("raccoon mario"));
	}
}
