#include "FireBall.h"
#include "../Mario/Mario.h"
#include "../../Core/ObjectState.h"
#include "../Mario/MarioChangeFigureState.h"
#include "../Mario/MarioDeathState.h"

FireBall::FireBall(VECTOR2D begin, float maxLength): GameObject(new ObjectState())
{
	this->_begin = begin;
	this->_maxLength = maxLength;
	this->_width = 9;
	this->_height = 9;
	this->_name = "fire ball";
	this->_position = begin;
}

void FireBall::Update(float deltaTime)
{
	if (this->_isActive == false)
	{
		return;
	}
	VECTOR2D temp = GetWorldPosition() - this->_begin;
	float length = D3DXVec2Length(&temp);
	if (length > this->_maxLength)
	{
		this->_isActive = false;
		this->_velocity = VECTOR2D(0.0f, 0.0f);
	}
	GameObject::Update(deltaTime);
	VECTOR2D pos = GetWorldPosition();
	//DebugOut((wchar_t*)L"[INFO] Fire Ball pos x = %f, y = %f \n", pos.x, pos.y);
}

void FireBall::Render()
{
	GameObject::Render(-0.1f);
}

void FireBall::OnCollision(CollisionEvent colEvent)
{
	Mario* mario = dynamic_cast<Mario*>(colEvent.collisionObj);

	if (mario != nullptr)
	{
		this->_isActive = false;
		this->_velocity = VECTOR2D(0.0f, 0.0f);

		string stateName = mario->GetStateName();
		if (mario->name != "small mario" && stateName.find("change figure") == string::npos)
		{
			mario->TransitionTo(new MarioChangeFigureState("small mario"));
		}
		else if (stateName.find("change figure") == string::npos)
		{
			mario->TransitionTo(new MarioDeathState());
		}
	}
}

Renderable* FireBall::GetRenderable()
{
	AnimationService* animations = AnimationService::GetInstance();
	return animations->GetAnimation("fire ball");
}

