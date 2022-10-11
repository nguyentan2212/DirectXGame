#include "ObjectState.h"
#include "GameObject.h"

ObjectState::~ObjectState()
{
	delete this->_context;
}
