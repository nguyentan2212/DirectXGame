#include "VenusFireTrap.h"
#include "../../Core/GameObject.h"
#include "VenusFireTrapSleepState.h"

VenusFireTrap::VenusFireTrap(): GameObject(new VenusFireTrapSleepState())
{
	this->_name = "venus fire trap";
	this->_width = FIRE_TRAP_WIDTH;
	this->_height = FIRE_TRAP_HEIGHT;
}

void VenusFireTrap::Update(float deltaTime)
{
	if (this->_isActive == false)
	{
		return;
	}

	this->_state->Update(deltaTime);
	GameObject::Update(deltaTime);
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
