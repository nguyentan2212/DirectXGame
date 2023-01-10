#include "Mario.h"
#include "../GUI.h"
#include "../../Physic/CollisionManager.h"
#include "../../Core/KeyboardHandler.h"

Mario::Mario(ObjectState* state): GameObject(state)
{
	this->_showBoundingBox = true;
	this->_name = "mario";
	ChangeFigure(MARIO_SMALL);
}

void Mario::Update(float deltaTime)
{
	if (this->_isActive == false)
	{
		return;
	}

	GameObject::Update(deltaTime);

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
	this->_state->Update(deltaTime);

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
	if (keyCode == DIK_X && keyboard->IsKeyDown(DIK_LCONTROL))
	{
		ChangeFigure(MARIO_SMALL);
	}
	else if (keyCode == DIK_R && keyboard->IsKeyDown(DIK_LCONTROL))
	{
		ChangeFigure(MARIO_RACCOON);
	}
	else if (keyCode == DIK_S && keyboard->IsKeyDown(DIK_LCONTROL))
	{
		ChangeFigure(MARIO_SUPER);
	}
	this->_state->OnKeyDown(keyCode);
}

void Mario::OnKeyUp(int keyCode)
{
	this->_state->OnKeyUp(keyCode);
}

void Mario::OnCollision(CollisionEvent colEvent)
{
	string objName = colEvent.collisionObj->name;
	if (objName == "pine" || objName == "ground" || objName == "cloud" || objName == "mushroom brick" || objName == "leaf brick")
	{
		if (colEvent.direction == Direction::DOWN)
		{
			this->_isGrounded = true;
			this->_position += this->_velocity * colEvent.entryTime;
			this->_velocity = VECTOR2D(this->_velocity.x, 0);
			this->_acceleration = VECTOR2D(this->_acceleration.x, 0.0f);
		}
	}
	this->_state->OnCollision(colEvent);
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

Renderable* Mario::GetRenderable()
{
	string aniName;
	switch (this->_figure)
	{
	case MARIO_SMALL:
	{
		aniName = "small mario";
		break;
	}
	case MARIO_SUPER:
	{
		aniName = "super mario";
		break;
	}
	default:
	{
		aniName = "raccoon mario";
		break;
	}
	}
	aniName = aniName + " " + this->_state->name;

	AnimationService* animations = AnimationService::GetInstance();
	return animations->GetAnimation(aniName);
}

void Mario::ChangeFigure(UINT figure)
{
	switch (figure)
	{
	case MARIO_SMALL:
	{
		this->_height = MARIO_SMALL_HEIGHT;
		this->_width = MARIO_SMALL_WIDTH;
		if (this->_figure != MARIO_SMALL)
		{
			this->_position = this->_position + VECTOR2D(0.0f, (MARIO_SMALL_HEIGHT - MARIO_SUPER_HEIGHT) / 2.0f);
		}
		break;
	}
	case MARIO_SUPER:
	{
		this->_height = MARIO_SUPER_HEIGHT;
		this->_width = MARIO_SUPER_WIDTH;
		if (this->_figure == MARIO_SMALL)
		{
			this->_position = this->_position + VECTOR2D(0.0f, (MARIO_SUPER_HEIGHT - MARIO_SMALL_HEIGHT) / 2.0f);
		}
		break;
	}
	case MARIO_RACCOON:
	{
		this->_height = MARIO_RACCOON_HEIGHT;
		this->_width = MARIO_RACCOON_WIDTH;
		if (this->_figure == MARIO_SMALL)
		{
			this->_position = this->_position + VECTOR2D(0.0f, (MARIO_SUPER_HEIGHT - MARIO_SMALL_HEIGHT) / 2.0f);
		}
		break;
	}
	default:
		break;
	}
	this->_figure = figure;
}
