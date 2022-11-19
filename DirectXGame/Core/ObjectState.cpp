#include "ObjectState.h"
#include "GameObject.h"
#include "Camera.h"

ObjectState::~ObjectState()
{
}

Box ObjectState::GetBoundingBox()
{
	Camera* camera = Camera::GetInstance();

	VECTOR2D result = this->_context->GetWorldPosition() - camera->position;
	result -= VECTOR2D(this->_width, this->_height) / 2;

	return Box(result.x, result.y, this->_width, this->_height);
}

void ObjectState::OnCollision(CollisionEvent colEvent)
{
}
