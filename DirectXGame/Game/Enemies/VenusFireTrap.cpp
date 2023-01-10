#include "VenusFireTrap.h"
#include "../../Core/GameObject.h"
#include "VenusFireTrapSleepState.h"

VenusFireTrap::VenusFireTrap(): GameObject(new VenusFireTrapSleepState())
{
	this->_name = "venus fire trap";
	this->_width = 16;
	this->_height = 32;
}

void VenusFireTrap::Update(float deltaTime)
{
	this->_state->Update(deltaTime);
	GameObject::Update(deltaTime);
	VECTOR2D pos = GetWorldPosition();

	//DebugOut((wchar_t*)L"[INFO] Venus Fire Trap pos x = %f, y = %f \n", pos.x, pos.y);
}

void VenusFireTrap::Render()
{
	_isFlipped = this->_direction == DIRECTION::LEFT ? false : true;
	GameObject::Render(0.4f);
}

void VenusFireTrap::OnCollision(CollisionEvent colEvent)
{
}

Renderable* VenusFireTrap::GetRenderable()
{
	string stateName = this->_name + " " +  this->_state->name;

	AnimationService* animations = AnimationService::GetInstance();
	return animations->GetAnimation(stateName);
}
