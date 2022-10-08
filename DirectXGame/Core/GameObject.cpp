#include "GameObject.h"

GameObject::GameObject(Animation* animation)
{
	this->_position = Vector();
	this->_animation = animation;
}

GameObject::~GameObject()
{
	delete this->_animation;
}

void GameObject::Update(float deltaTime)
{
	this->_animation->Update(deltaTime);
}

void GameObject::Render()
{
	this->_animation->Render(this->_position.x, this->_position.y);
}

void GameObject::OnKeyUp(int keyCode)
{
}

void GameObject::OnKeyDown(int keyCode)
{
}
