#include "Mario.h"
#include "../GUI.h"
#include "../../Physic/CollisionManager.h"
#include "../../Core/KeyboardHandler.h"

Mario::Mario(): GameObject()
{
	this->_showBoundingBox = true;
	this->_name = "mario";
	Jump(0);
	ChangeFigure(MARIO_SMALL);
}

void Mario::Update(float deltaTime)
{
	if (this->_isActive == false)
	{
		return;
	}

	Renderable* r = GetRenderable();
	if (r != nullptr)
	{
		r->Update(deltaTime);
	}

	if (this->_velocity.x < 0)
	{
		this->_direction = DIRECTION::LEFT;
	}
	else if (this->_velocity.x > 0)
	{
		this->_direction = DIRECTION::RIGHT;
	}

	this->_acceleration = VECTOR2D(this->_acceleration.x, -MARIO_GRAVITY);
	this->_velocity += this->_acceleration * deltaTime / 1000;
	if (abs(this->_velocity.x) > MARIO_RUN_MAX_SPEED_X)
	{
		this->_velocity.x = this->_velocity.x > 0 ? MARIO_RUN_MAX_SPEED_X : -MARIO_RUN_MAX_SPEED_X;
	}

	this->_isGrounded = false;
	CollisionManager::Processing(this, deltaTime);

	Translate(this->_velocity * deltaTime / 1000);
}

void Mario::Render()
{
	_isFlipped = this->_direction == DIRECTION::LEFT ? false : true;
	GameObject::Render(-0.1);
}

void Mario::OnKeyDown(int keyCode)
{
	KeyboardHandler* keyboard = KeyboardHandler::GetInstance();
	switch (keyCode)
	{
	case DIK_X:
		if (keyboard->IsKeyDown(DIK_LCONTROL))
		{
			ChangeFigure(MARIO_SMALL);
		}
		break;
	case DIK_L:
		if (keyboard->IsKeyDown(DIK_LCONTROL))
		{
			ChangeFigure(MARIO_SUPER);
		}
		break;
	case DIK_R:
		if (keyboard->IsKeyDown(DIK_LCONTROL))
		{
			ChangeFigure(MARIO_RACCOON);
		}
		break;
	case DIK_A:
		Run(-MARIO_X_ACCE);
		break;
	case DIK_D:
		Run(MARIO_X_ACCE);
		break;
	case DIK_W:
		if (this->_isGrounded)
		{
			Jump(MARIO_JUMP_SPEED_Y);
		}
		break;
	case DIK_S:
		if (this->_isGrounded)
		{
			Sit();
		}
		break;
	default:
		break;
	}
}

void Mario::OnKeyUp(int keyCode)
{
	switch (keyCode)
	{
	case DIK_A:
	case DIK_D:
		if (GetState() == MARIO_RUN)
		{
			Idle();
		}
		break;
	case DIK_S:
		Idle();
	default:
		break;
	}
}

void Mario::OnCollision(CollisionEvent colEvent)
{
	if (GetState() == MARIO_DEATH)
	{
		return;
	}
	GameObject* obj = colEvent.collisionObj;
	string objName = colEvent.collisionObj->name;
	string className = typeid(*colEvent.collisionObj).name();
	if (className == "class Platform" || className == "class Brick")
	{
		if (colEvent.direction == Direction::DOWN)
		{
			Grounding(colEvent.entryTime);
			if (GetState() == MARIO_JUMP)
			{
				Idle();
			}
		}
		if (objName != "panel" && (colEvent.direction == Direction::LEFT || colEvent.direction == Direction::RIGHT))
		{
			this->_velocity = VECTOR2D(0.0f, this->_velocity.y);
			this->_acceleration = VECTOR2D(0.0f, this->_acceleration.y);
		}
		if (className == "class Brick" && colEvent.direction == Direction::UP)
		{
			this->_position += this->_velocity * colEvent.entryTime;
			Jump(0);
		}
	}
	if (objName == "mushroom")
	{
		ChangeFigure(MARIO_SUPER);
	}
	else if (objName == "leaf")
	{
		ChangeFigure(MARIO_RACCOON);
	}
	if (objName == "fire ball" || objName == "goomba")
	{
		if (GetState("figure") != MARIO_SMALL)
		{
			this->ChangeFigure(MARIO_SMALL);
		}
		else
		{
			Death();
		}
	}
}

void Mario::IncreaseScore(int score)
{
	GameObject* temp = GetChildWithName("gui");
	if (temp != nullptr)
	{
		GUI* gui = dynamic_cast<GUI*>(temp);
		if (gui != nullptr)
		{
			gui->IncreaseScore(score);
		}
	}
}

void Mario::IncreaseCoin(int coin)
{
	GameObject* temp = GetChildWithName("gui");
	if (temp != nullptr)
	{
		GUI* gui = dynamic_cast<GUI*>(temp);
		if (gui != nullptr)
		{
			gui->IncreaseCoin(coin);
		}
	}
}

void Mario::UpdateRunSpeed(float speed)
{
	GameObject* temp = GetChildWithName("gui");
	if (temp != nullptr)
	{
		GUI* gui = dynamic_cast<GUI*>(temp);
		if (gui != nullptr)
		{
			gui->UpdateRunSpeed(abs(speed));
		}
	}
}

void Mario::SetState(UINT stateValue, string stateName)
{
	this->_states[stateName] = stateValue;
}

Renderable* Mario::GetRenderable()
{
	string aniName = figureNames[GetState("figure")] + " " + aniNames[GetState("default")];

	AnimationService* animations = AnimationService::GetInstance();
	return animations->GetAnimation(aniName);
}

void Mario::ChangeFigure(UINT figure)
{
	this->_position = this->_position + VECTOR2D(0.0f, (mario_sizes[figure].second - this->_height) / 2 + 0.5f);
	this->_width = mario_sizes[figure].first;
	this->_height = mario_sizes[figure].second;
	this->_figure = figure;
	SetState(figure, "figure");
}

void Mario::Idle()
{
	if (GetState() == MARIO_SIT)
	{
		this->position = this->position - VECTOR2D(0.0f, (this->_height - mario_sizes[GetState("figure")].second) / 2);
		this->_height = mario_sizes[GetState("figure")].second;
	}
	SetState(MARIO_IDLE);
	this->_velocity = VECTOR2D(0.0f, 0.0f);
	this->_acceleration = VECTOR2D(0.0f, 0.0f);
}

void Mario::Run(float acce_x)
{
	if (this->_isGrounded == false)
	{
		this->acceleration = VECTOR2D(0.0f, this->acceleration.y);
		this->velocity = VECTOR2D(acce_x, this->velocity.y);
		return;
	}
	SetState(MARIO_RUN);
	this->_velocity = VECTOR2D(0.0f, 0.0f);
	this->_acceleration = VECTOR2D(acce_x, 0.0f);
}

void Mario::Jump(float speed)
{
	SetState(MARIO_JUMP);
	VECTOR2D vec = this->velocity;
	vec.y = speed;
	this->velocity = vec;
	this->acceleration = VECTOR2D(0.0f, 0.0f);
}

void Mario::Sit()
{
	if (GetState() != MARIO_IDLE || GetState("figure") == MARIO_SMALL)
	{
		return;
	}
	SetState(MARIO_SIT);
	this->_velocity = VECTOR2D(0.0f, 0.0f);
	this->_acceleration = VECTOR2D(0.0f, 0.0f);
	this->position = this->position - VECTOR2D(0.0f, (this->_height - MARIO_SIT_HEIGHT) / 2);
	this->_height = MARIO_SIT_HEIGHT;
}

void Mario::Death()
{
	SetState(MARIO_DEATH);
	this->velocity = VECTOR2D(0.0f, 100);
	this->acceleration = VECTOR2D(this->acceleration.x, -MARIO_GRAVITY);
}

void Mario::Untouchable()
{
}
