#include "ObjectState.h"
#include "GameObject.h"
#include "../Graphic/Graphic.h"

ObjectState::~ObjectState()
{
}

Box ObjectState::GetBoundingBox()
{
	Graphic* graphic = Graphic::GetInstance();

	VECTOR2D result = this->_context->GetWorldPosition() - graphic->cameraPosition;
	result -= VECTOR2D(this->_width, this->_height) / 2;

	return Box(result.x, result.y, this->_width, this->_height);
}
