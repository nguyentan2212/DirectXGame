#include "MarioChangeFigureState.h"
#include "../../Core/GameObject.h"
#include "MarioIdleState.h"

MarioChangeFigureState::MarioChangeFigureState(string newFigure)
{
	this->_name = "change figure " + newFigure;
	this->_newFigure = newFigure;
	DebugOut((wchar_t*)L"[INFO] Mario transition to Run State \n");
}

void MarioChangeFigureState::OnTransition()
{
	this->_context->width = 16.0f;
	this->_context->height = 28.0f;
	this->_context->velocity = VECTOR2D(0.0f, 0.0f);
	this->_context->acceleration = VECTOR2D(0.0f, 0.0f);

	if (this->_newFigure == "small mario")
	{
		this->_context->width = 15.0f;
		this->_context->height = 16.0f;
		if (this->_context->name == "super mario")
		{
			this->_context->position = VECTOR2D(this->_context->position.x, this->_context->position.y - 6.5f);
		}
		else if (this->_context->name == "raccoon mario")
		{
			this->_context->position = VECTOR2D(this->_context->position.x, this->_context->position.y - 5.5f);
		}
	}
	else if (this->_newFigure == "super mario")
	{
		this->_context->width = 16.0f;
		this->_context->height = 28.0f;
		if (this->_context->name == "small mario")
		{
			this->_context->position = VECTOR2D(this->_context->position.x, this->_context->position.y + 6.5f);
		}
		else if (this->_context->name == "raccoon mario")
		{
			this->_context->position = VECTOR2D(this->_context->position.x, this->_context->position.y + 0.5f);
		}
	}
	else if (this->_newFigure == "raccoon mario")
	{
		this->_context->width = 23.0f;
		this->_context->height = 27.0f;
		if (this->_context->name == "small mario")
		{
			this->_context->position = VECTOR2D(this->_context->position.x, this->_context->position.y + 5.5f);
		}
		else if (this->_context->name == "super mario")
		{
			this->_context->position = VECTOR2D(this->_context->position.x, this->_context->position.y - 0.5f);
		}
	}
}

void MarioChangeFigureState::Update(float deltaTime)
{
	this->_coolDown -= deltaTime;
	if (this->_coolDown <= 0)
	{
		this->_context->name = this->_newFigure;
		this->_context->TransitionTo(new MarioIdleState());
	}
}
