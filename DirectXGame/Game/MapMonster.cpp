#include "MapMonster.h"

MapMonster::MapMonster(VECTOR2D pos): GameObject()
{
	this->_velocity = VECTOR2D(-SPEED, 0.0f);
	this->_firstPos = pos;
	AnimationService* anis = AnimationService::GetInstance();
	this->_renderable = anis->GetAnimation("monster");
}

void MapMonster::Update(float deltaTime)
{
	this->_distance -= abs(this->_velocity.x * deltaTime / 1000.0f);
	Translate(this->_velocity * deltaTime / 1000.0f);

	if (this->_distance <= 0)
	{
		this->_distance = DISTANCE;
		if (this->_velocity.x < 0)
		{
			this->position = this->_firstPos;
			this->_isFlipped = true;
		}
		else
		{
			this->position = this->_firstPos + VECTOR2D(DISTANCE, 0.0f);
			this->_isFlipped = false;
		}
		
		this->_velocity *= -1;
	}
}
