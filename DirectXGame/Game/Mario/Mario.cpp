#include "Mario.h"
#include "../GUI.h"
#include "../../Physic/CollisionManager.h"
#include "../../Core/KeyboardHandler.h"
#include "../Enemies/KoopaParaTroopa.h"
#include "../Enemies/KoopaTroopa.h"
#include "../Items/Brick.h"

Mario::Mario(): GameObject()
{
	this->_showBoundingBox = true;
	this->_name = "mario";
	this->_preFigure = figureNames[MARIO_SMALL];
	SetState(MARIO_SMALL,"figure");
	SetState(MARIO_NOT_HOLD, "hold");
	SetState(MARIO_TOUCHABLE, "touchable");
	ChangeFigure(MARIO_SMALL);
	Jump(0);
}

void Mario::Update(float deltaTime)
{
	if (this->_isActive == false)
	{
		return;
	}

	if (GetState("touchable") == MARIO_UNTOUCHABLE)
	{
		this->_untouchableTime -= deltaTime;
		if (this->_untouchableTime < 0)
		{
			this->_untouchableTime = UNTOUCHABLE_TIME;
			SetState(MARIO_TOUCHABLE, "touchable");
		}
	}

	if (GetState() == MARIO_IDLE && this->_isGrounded == true)
	{
		if (IsKeyDown(BTN_LEFT))
		{
			Run(F_LEFT);
		}
		else if (IsKeyDown(BTN_RIGHT))
		{
			Run(F_RIGHT);
		}
		else
		{
			Idle();
		}
	}

	if (IsKeyDown(BTN_A))
	{
		if (GetState() == MARIO_FLY && this->_flyingTime > 0)
		{
			this->_flyingTime -= deltaTime;
			this->_acceleration = VECTOR2D(0.0f, 0.0f);
		}
		else if (GetState() == MARIO_FLY)
		{
			this->_acceleration = VECTOR2D(this->_acceleration.x, -MARIO_EXTRA_WEEK_GRAVITY);
		}
		else
		{
			this->_acceleration = VECTOR2D(this->_acceleration.x, -MARIO_WEEK_GRAVITY);
		}
	}
	else
	{
		this->_acceleration = VECTOR2D(this->_acceleration.x, -MARIO_GRAVITY);
	}

	this->_velocity += this->_acceleration * deltaTime / 1000;
	if (abs(this->_velocity.x) > MARIO_RUN_MAX_SPEED_X)
	{
		this->_velocity.x = this->_velocity.x > 0 ? MARIO_RUN_MAX_SPEED_X : -MARIO_RUN_MAX_SPEED_X;
	}

	this->_isGrounded = false;
	CollisionManager::Processing(this, deltaTime);

	if (this->_isGrounded == false && GetState() != MARIO_JUMP 
		&& GetState() != MARIO_DEATH && GetState() != MARIO_FLY)
	{
		Jump(0);
	}

	if (this->_velocity.x < 0)
	{
		this->_direction = DIRECTION::LEFT;
	}
	else if (this->_velocity.x > 0)
	{
		this->_direction = DIRECTION::RIGHT;
	}
	Translate(this->_velocity * deltaTime / 1000);
	//DebugOut(L"[INFO] Mario vel.x: %f !\n", this->velocity.x);
	if (IsKeyDown(BTN_B) && GetState("hold") == MARIO_HOLD)
	{
		Hold();
	}
	if (GetState() == MARIO_KICK)
	{
		if (this->_kickTime > 0)
		{
			this->_kickTime -= deltaTime;
		}
		else
		{
			this->_kickTime = KICK_TIME;
			Idle();
		}
	}
}

void Mario::Render()
{
	_isFlipped = this->_direction == DIRECTION::LEFT ? false : true;
	GameObject::Render(-0.1);
}

void Mario::OnKeyDown(int keyCode)
{
	if (GetState() == MARIO_DEATH)
	{
		return;
	}

	switch (keyCode)
	{
	case DIK_1:
		if (IsKeyDown(DIK_LCONTROL))
		{
			ChangeFigure(MARIO_SMALL);
		}
		break;
	case DIK_2:
		if (IsKeyDown(DIK_LCONTROL))
		{
			ChangeFigure(MARIO_SUPER);
		}
		break;
	case DIK_3:
		if (IsKeyDown(DIK_LCONTROL))
		{
			ChangeFigure(MARIO_RACCOON);
		}
		break;
	case BTN_LEFT:
		Run(F_LEFT);
		break;
	case BTN_RIGHT:
		Run(F_RIGHT);
		break;
	case BTN_UP:
		if (this->_isGrounded)
		{
			Jump(MARIO_JUMP_SPEED_Y);
		}
		break;
	case BTN_DOWN:
		if (this->_isGrounded)
		{
			Sit();
		}
		break;
	case BTN_A:
		if (GetState() == MARIO_RUN && abs(this->velocity.x) == MARIO_RUN_MAX_SPEED_X
			&& GetState("figure") == MARIO_RACCOON)
		{
			Fly();
		}
		break;
	case BTN_B:
		if (IsKeyDown(BTN_LEFT))
		{
			Run(F_LEFT);
		}
		else if (IsKeyDown(BTN_RIGHT))
		{
			Run(F_RIGHT);
		}
	default:
		break;
	}
}

void Mario::OnKeyUp(int keyCode)
{
	switch (keyCode)
	{
	case BTN_LEFT:
	case BTN_RIGHT:
		if (GetState() == MARIO_RUN)
		{
			Idle();
		}
		break;
	case BTN_DOWN:
		Idle();
		break;
	case BTN_A:
		break;
	case BTN_B:
		if (GetState("hold") == MARIO_HOLD)
		{
			Kick();
		}
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

	string className = typeid(*colEvent.collisionObj).name();
	UINT t = GetState("touchable");

	if (className == "class Platform")
	{
		OnCollisionWithPlatform(colEvent);
	}
	else if (className == "class Brick")
	{
		OnCollisionWithBrick(colEvent);
	}
	else if (className == "class Goomba" && GetState("touchable") != MARIO_UNTOUCHABLE)
	{
		OnCollisionWithGoomba(colEvent);
	}
	else if (className == "class ParaGoomba" && GetState("touchable") != MARIO_UNTOUCHABLE)
	{
		OnCollisionWithParaGoomba(colEvent);
	}
	else if (className == "class KoopaParaTroopa" && GetState("touchable") != MARIO_UNTOUCHABLE)
	{
		OnCollisionWithKoopaParaTroopa(colEvent);
	}
	else if (className == "class KoopaTroopa" && GetState("touchable") != MARIO_UNTOUCHABLE)
	{
		OnCollisionWithKoopaTroopa(colEvent);
		
	}
	else
	{
		OnCollisionWithItem(colEvent);
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
	string aniName = figureNames[GetState("figure")];

	if (GetState("touchable") == MARIO_UNTOUCHABLE && figureNames[GetState("figure")] != this->_preFigure)
	{
		aniName = aniName + " untouchable " + this->_preFigure;
	}
	else
	{
		aniName = aniName + " " + aniNames[GetState("default")];
	}

	if (GetState("hold") == MARIO_HOLD && (GetState() == MARIO_IDLE || GetState() == MARIO_RUN || GetState() == MARIO_JUMP))
	{
		aniName = aniName + " hold";
	}

	if (GetState() == MARIO_RUN && abs(this->velocity.x) == MARIO_RUN_MAX_SPEED_X && GetState("hold") == MARIO_NOT_HOLD
		&& GetState("figure") == MARIO_RACCOON)
	{
		aniName = aniName + " fast";
	}

	AnimationService* animations = AnimationService::GetInstance();
	return animations->GetAnimation(aniName);
}

void Mario::Grounding(float time)
{
	GameObject::Grounding(time);
	if (GetState() == MARIO_JUMP || GetState() == MARIO_FLY)
	{
		Idle();
	}
}

void Mario::ChangeFigure(UINT figure)
{
	this->_position = this->_position + VECTOR2D(0.0f, (mario_sizes[figure].second - this->_height) / 2 + 0.5f);
	this->_width = mario_sizes[figure].first;
	this->_height = mario_sizes[figure].second;

	this->_preFigure = figureNames[GetState("figure")];
	SetState(figure, "figure");
	SetState(MARIO_UNTOUCHABLE, "touchable");
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

void Mario::Run(float direction)
{
	if (this->_isGrounded == false)
	{
		if (this->velocity.x == 0.0f)
		{
			this->velocity = VECTOR2D(MARIO_RUN_LOW_SPEED * direction, this->velocity.y);
		}
		else if (this->velocity.x * direction < 0)
		{
			this->_velocity.x = direction * abs(this->_velocity.x);
		}
		return;
	}

	SetState(MARIO_RUN);
	if (IsKeyDown(BTN_B) && GetState("hold") == MARIO_NOT_HOLD)
	{
		this->_acceleration = VECTOR2D(MARIO_X_ACCE * direction, 0.0f);
		DebugOut(L"[INFO] Mario fast run !\n");
	}
	else
	{
		this->_acceleration = VECTOR2D(0.0f, 0.0f);
	}
	this->_velocity = VECTOR2D(MARIO_RUN_LOW_SPEED * direction, 0.0f);
}

void Mario::Jump(float speed)
{
	SetState(MARIO_JUMP);
	VECTOR2D vec = this->velocity;
	vec.y = speed;
	this->velocity = vec;
	this->acceleration = VECTOR2D(0.0f, 0.0f);
}

void Mario::Fly()
{
	SetState(MARIO_FLY);
	this->_flyingTime = MARIO_FLYING_TIME;
	VECTOR2D vec = this->velocity;
	vec.y = MARIO_JUMP_SPEED_Y;
	this->velocity = vec;
	this->acceleration = VECTOR2D(0.0f, 0.0f);
}

void Mario::Sit()
{
	if (GetState() != MARIO_IDLE || GetState("figure") == MARIO_SMALL || GetState("hold") == MARIO_HOLD)
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
	this->velocity = VECTOR2D(0.0f, MARIO_JUMP_DEFLECT_SPEED);
	this->acceleration = VECTOR2D(0.0f, -MARIO_GRAVITY);
}

void Mario::Untouchable()
{
}

void Mario::Hold()
{
	if (this->_holdObj == nullptr)
	{
		return;
	}
	VECTOR2D pos = this->position;
	if (this->velocity.x > 0)
	{
		this->_holdObj->position = pos + VECTOR2D(this->_width / 1.5f, 0.0f);
	}
	else if (this->velocity.x < 0)
	{
		this->_holdObj->position = pos - VECTOR2D(this->_width / 1.5f, 0.0f);
	}
	else
	{
		if (this->direction == DIRECTION::LEFT)
		{
			this->_holdObj->position = pos - VECTOR2D(this->_width / 1.5f, 0.0f);
		}
		else
		{
			this->_holdObj->position = pos + VECTOR2D(this->_width / 1.5f, 0.0f);
		}
	}
}

void Mario::Kick()
{
	SetState(MARIO_KICK);
	if (this->velocity.x > 0)
	{
		this->_holdObj->direction = DIRECTION::RIGHT;
	}
	else if (this->velocity.x < 0)
	{
		this->_holdObj->direction = DIRECTION::LEFT;
	}
	else
	{
		this->_holdObj->direction = this->direction;
	}

	string className = typeid(*this->_holdObj).name();

	if (className == "class KoopaParaTroopa")
	{
		this->_holdObj->SetState(KOOPA_PARATROOPA_RUN);
	}
	else if (className == "class KoopaTroopa")
	{
		this->_holdObj->SetState(KOOPA_TROOPA_RUN);
	}
	this->_holdObj = nullptr;
	SetState(MARIO_NOT_HOLD, "hold");
}

void Mario::OnCollisionWithPlatform(CollisionEvent colEvent)
{
	if (colEvent.direction == Direction::DOWN)
	{
		Grounding(colEvent.entryTime);
	}
	if (colEvent.collisionObj->name != "panel" && (colEvent.direction == Direction::LEFT || colEvent.direction == Direction::RIGHT))
	{
		//DebugOut(L"[INFO] Mario v.x: %f, v.y = %f !\n", this->velocity.x, this->velocity.y);
		this->_position += this->_velocity * colEvent.entryTime;
		this->_velocity = VECTOR2D(0.0f, this->_velocity.y);
		this->_acceleration = VECTOR2D(0.0f, this->_acceleration.y);
	}
	else if (colEvent.direction == Direction::UP)
	{
		VECTOR2D pos = this->position;
		pos.x += this->_velocity.x * colEvent.entryTime;
		this->position = pos;
		this->velocity = VECTOR2D(0.0f, 0.0f);
	}

}

void Mario::OnCollisionWithBrick(CollisionEvent colEvent)
{
	if (colEvent.direction == Direction::DOWN)
	{
		Grounding(colEvent.entryTime);
	}
	else if (colEvent.direction == Direction::LEFT || colEvent.direction == Direction::RIGHT)
	{
		VECTOR2D pos = this->position;
		pos.x += this->_velocity.x * colEvent.entryTime;
		this->position = pos;
		this->velocity = VECTOR2D(0.0f, 0.0f);
		DebugOut(L"[INFO] Mario collide with brick pos.x: %f !\n", this->position.x);
	}
	else
	{
		VECTOR2D pos = this->position;
		pos.y = this->velocity.y * colEvent.entryTime;
		this->_velocity = VECTOR2D(this->_velocity.x, 0.0f);
		this->_acceleration = VECTOR2D(this->_acceleration.x, -MARIO_GRAVITY);
		if (colEvent.collisionObj->GetState() == BRICK_UNTOUCHED && colEvent.collisionObj->name == "brick")
		{
			IncreaseCoin();
			IncreaseScore(SCORE_COIN_BRICK);
		}
	}
}

void Mario::OnCollisionWithItem(CollisionEvent colEvent)
{
	if (colEvent.collisionObj->name == "mushroom")
	{
		ChangeFigure(MARIO_SUPER);
		IncreaseScore(SCORE_POWER_MUSHROOM);
	}
	else if (colEvent.collisionObj->name == "leaf")
	{
		ChangeFigure(MARIO_RACCOON);
		IncreaseScore(SCORE_LEAF);
	}
}

void Mario::OnCollisionWithGoomba(CollisionEvent colEvent)
{
	if (colEvent.direction == Direction::DOWN)
	{
		IncreaseScore(100);
		if (IsKeyDown(DIK_W))
		{
			Jump(MARIO_SUPER_JUMP_Y);
		}
		else
		{
			Jump(MARIO_JUMP_SPEED_Y);
		}
	}
	else if (GetState("figure") != MARIO_SMALL && GetState() != MARIO_ATTACK)
	{
		this->ChangeFigure(MARIO_SMALL);
	}
	else if (GetState() != MARIO_ATTACK)
	{
		Death();
	}
}

void Mario::OnCollisionWithParaGoomba(CollisionEvent colEvent)
{
	if (colEvent.direction == Direction::DOWN)
	{
		if (IsKeyDown(DIK_W))
		{
			Jump(MARIO_SUPER_JUMP_Y);
		}
		else
		{
			Jump(MARIO_JUMP_SPEED_Y);
		}
	}
	else if (GetState("figure") != MARIO_SMALL && GetState() != MARIO_ATTACK)
	{
		this->ChangeFigure(MARIO_SMALL);
	}
	else if (GetState() != MARIO_ATTACK)
	{
		Death();
	}
}

void Mario::OnCollisionWithKoopaParaTroopa(CollisionEvent colEvent)
{
	DebugOut(L"[INFO] Collide with koopa paratroopa !\n");
	if (colEvent.collisionObj->GetState() == KOOPA_PARATROOPA_STUN)
	{
		if (GetState() == MARIO_RUN && IsKeyDown(BTN_B))
		{
			SetState(MARIO_HOLD, "hold");
			this->_holdObj = colEvent.collisionObj;
			this->_holdObj->SetState(KOOPA_PARATROOPA_IS_HELD);
		}
	}
	else if (colEvent.collisionObj->GetState() != KOOPA_PARATROOPA_RUN)
	{
		if (colEvent.direction == Direction::DOWN)
		{
			colEvent.collisionObj->SetState(KOOPA_PARATROOPA_STUN);
			if (IsKeyDown(DIK_W))
			{
				Jump(MARIO_SUPER_JUMP_Y);
			}
			else
			{
				Jump(MARIO_JUMP_SPEED_Y);
			}
		}
		else if (GetState("figure") != MARIO_SMALL && GetState() != MARIO_ATTACK)
		{
			this->ChangeFigure(MARIO_SMALL);
		}
		else if (GetState() != MARIO_ATTACK)
		{
			Death();
		}
	}
	else if (GetState("figure") != MARIO_SMALL)
	{
		this->ChangeFigure(MARIO_SMALL);
	}
	else
	{
		Death();
	}
}

void Mario::OnCollisionWithKoopaTroopa(CollisionEvent colEvent)
{
	DebugOut(L"[INFO] Collide with koopa troopa !\n");
	if (colEvent.collisionObj->GetState() == KOOPA_TROOPA_STUN)
	{
		if (GetState() == MARIO_RUN && IsKeyDown(BTN_B))
		{
			SetState(MARIO_HOLD, "hold");
			this->_holdObj = colEvent.collisionObj;
			this->_holdObj->SetState(KOOPA_TROOPA_IS_HELD);
		}
	}
	else if (colEvent.collisionObj->GetState() != KOOPA_TROOPA_RUN)
	{
		if (colEvent.direction == Direction::DOWN)
		{
			colEvent.collisionObj->SetState(KOOPA_TROOPA_STUN);
			if (IsKeyDown(DIK_W))
			{
				Jump(MARIO_SUPER_JUMP_Y);
			}
			else
			{
				Jump(MARIO_JUMP_SPEED_Y);
			}
		}
		else if (GetState("figure") != MARIO_SMALL && GetState() != MARIO_ATTACK)
		{
			this->ChangeFigure(MARIO_SMALL);
		}
		else if (GetState() != MARIO_ATTACK)
		{
			Death();
		}
	}
	else if (GetState("figure") != MARIO_SMALL)
	{
		this->ChangeFigure(MARIO_SMALL);
	}
	else
	{
		Death();
	}
}

bool Mario::IsKeyDown(int keyCode)
{
	KeyboardHandler* keyboard = KeyboardHandler::GetInstance();
	return keyboard->IsKeyDown(keyCode);
}