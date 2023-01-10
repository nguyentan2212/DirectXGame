#include "Text.h"
#include "../../Core/Camera.h"

Text::Text(Sprite* sprite, float beginY): GameObject(new ObjectState())
{
	this->_sprite = sprite;
	this->_velocity = VECTOR2D(0.0f, SCORE_SPEED);
	this->_beginY = beginY;
}

void Text::Update(float deltaTime)
{
	if (this->_isActive == false)
	{
		return;
	}

	Translate(this->_velocity * deltaTime / 1000);
	if (this->_position.y - this->_beginY > SCORE_MAX_HEIGHT)
	{
		this->_isActive = false;
	}
}

void Text::Render()
{
	if (this->_isActive == false)
	{
		return;
	}

	Camera* camera = Camera::GetInstance();
	this->_sprite->Render(this->_position - camera->position);
}
