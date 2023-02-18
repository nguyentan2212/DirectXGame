#include "Leaf.h"
#include "../../Graphic/SpriteService.h"
#include "../../Physic/CollisionManager.h"
#include "../Mario/Mario.h"

Leaf::Leaf(VECTOR2D pos): GameObject()
{
	this->position = pos;
	this->_height = LEAF_SIZE;
	this->_width = LEAF_SIZE;
	this->_velocity = VECTOR2D(0.0f, LEAF_Y_SPEED);
	this->_acceleration = VECTOR2D(0.0F, -LEAF_GRAVITY);
	this->_name = "leaf";

	SpriteService* sprites = SpriteService::GetInstance();
	this->_score = new GameObject(sprites->GetSprite("hub-and-font/1000"));
	this->_score->velocity = VECTOR2D(0.0f, LEAF_SCORE_SPEED);
	this->_score->isActive = false;
}

void Leaf::Update(float deltaTime)
{
	if (this->_isActive == false)
	{
		return;
	}
	// update score
	if (this->_score != nullptr)
	{
		this->_score->Update(deltaTime);
	}

	if (this->_score != nullptr && this->_score->isActive
		&& this->_score->position.y > this->_position.y + LEAF_SCORE_MAX_LENGHT)
	{
		this->_score->isActive = false;
		this->isActive = false;
	}

	// main update
	this->_velocity += this->_acceleration * deltaTime / 1000;
	CollisionManager::Processing(this, deltaTime);
	Translate(this->_velocity * deltaTime / 1000);
}

void Leaf::OnCollision(CollisionEvent colEvent)
{
	if (colEvent.collisionObj->name == "ground")
	{
		this->_acceleration = VECTOR2D();
		this->_velocity = VECTOR2D();
		this->_isActive = false;
	}
	else if (colEvent.collisionObj->name == "mario")
	{
		this->_score->isActive = true;
		this->_score->position = position + VECTOR2D(0.0f, LEAF_SIZE);
		Mario* mario = dynamic_cast<Mario*>(colEvent.collisionObj);
		mario->ChangeFigure(MARIO_RACCOON);
	}
}

void Leaf::Render()
{
	GameObject::Render();
	if (this->_score != nullptr && this->_score->isActive)
	{
		this->_score->Render(0.1f);
	}
}

Renderable* Leaf::GetRenderable()
{
	if (this->_score->isActive)
	{
		return nullptr;
	}

	SpriteService* sprites = SpriteService::GetInstance();
	return sprites->GetSprite("mics114");
}
