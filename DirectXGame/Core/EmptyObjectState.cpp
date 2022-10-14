#include "EmptyObjectState.h"

EmptyObjectState::EmptyObjectState(float width, float height)
{
	this->_width = width;
	this->_height = height;
}

void EmptyObjectState::Update(float deltaTime)
{
}

Animation* EmptyObjectState::GetAnimation()
{
	return nullptr;
}
