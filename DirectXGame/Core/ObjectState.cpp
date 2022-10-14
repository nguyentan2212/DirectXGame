#include "ObjectState.h"
#include "GameObject.h"

ObjectState::~ObjectState()
{
}

Box ObjectState::GetBoundingBox()
{
	VECTOR2D result = this->_context->GetWorldPosition();
	result -= VECTOR2D(this->_width, this->_height) / 2;

	return Box(result.x, result.y, this->_width, this->_height);
}
