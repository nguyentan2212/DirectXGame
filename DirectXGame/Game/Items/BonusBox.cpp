#include "BonusBox.h"
#include "../../Graphic/SpriteService.h"
#include "../../Graphic/AnimationService.h"
#include "../../Physic/CollisionManager.h"

BonusBox::BonusBox()
{
	this->_width = BONUS_BOX_SIZE;
	this->_height = BONUS_BOX_SIZE;
	SetState(UNTOUCHED);
	AnimationService* animations = AnimationService::GetInstance();
	this->_content = new GameObject(animations->GetAnimation("bonus"));
}

void BonusBox::Update(float deltaTime)
{
	CollisionManager::Processing(this, deltaTime);

	if (GetState() == TOUCHED)
	{
		if (this->_duration > 0)
		{
			this->_duration -= deltaTime;
		}
		else
		{
			this->_content->isActive = false;
		}
	}
	else
	{
		this->_content->position = this->position;
	}
	if (this->_content->isActive == true)
	{
		this->_content->Update(deltaTime);
	}
}

void BonusBox::OnCollision(CollisionEvent colEvent)
{
	if (colEvent.collisionObj->name == "mario" && colEvent.direction == DIRECTION::DOWN)
	{
		this->_content->velocity = VECTOR2D(0.0f, BONUS_BOX_SPEED);
		SetState(TOUCHED);

		AnimationService* animations = AnimationService::GetInstance();
		this->_content->SetRenderable(animations->GetAnimation("bonus")->GetCurrentSprite());
	}
}

void BonusBox::Render()
{
	GameObject::Render(0.1);
	if (this->_content->isActive == true)
	{
		this->_content->Render();
	}
}

Renderable* BonusBox::GetRenderable()
{
	SpriteService* sprites = SpriteService::GetInstance();
	return sprites->GetSprite("hub-and-font/empty-box");
}
