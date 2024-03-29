#include "Mario.h"
#include "../../Physic/CollisionManager.h"
#include "../../Core/KeyboardHandler.h"
#include "../Enemies/Enemies.h"
#include "../Items/Brick.h"
#include "../Scenes/CSceneOne.h"
#include "../Scenes/CSceneHidden.h"
#include "../../Core/GameEngine.h"

Mario::Mario(): GameObject()
{
	this->_showBoundingBox = true;
	this->_name = "mario";
	this->_preFigure = figureNames[MARIO_SMALL];
	SetState(MARIO_SMALL,"figure");
	SetState(MARIO_NOT_HOLD, "hold");
	SetState(MARIO_TOUCHABLE, "touchable");
	SetState(MARIO_BRICK_NOT_BLOCKING, "brick");
	ChangeFigure(MARIO_SMALL);
	Jump(0);
	this->_gui = new GUI();
	this->_isActive = false;
}

void Mario::Update(float deltaTime)
{
	this->_gui->Update(deltaTime);
	if (this->_isActive == false)
	{
		return;
	}

	if (this->position.y < -48.0f && GetState() != MARIO_DEATH)
	{
		Death();
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
		else if (GetState("figure") == MARIO_RACCOON)
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

	if (GetState() == MARIO_ATTACK)
	{
		if (this->_attackTime > 0)
		{
			this->_attackTime -= deltaTime;
		}
		else if (this->_isGrounded)
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
		else
		{
			Jump(0);
		}
	}

	if (abs(this->_velocity.x) > MARIO_RUN_MAX_SPEED_X)
	{
		this->_velocity.x = this->_velocity.x > 0 ? MARIO_RUN_MAX_SPEED_X : -MARIO_RUN_MAX_SPEED_X;
	}

	this->_isGrounded = false;
	SetState(MARIO_BRICK_NOT_BLOCKING, "brick");
	CollisionManager::Processing(this, deltaTime);

	if (this->_portal != nullptr)
	{
		VECTOR2D distance = this->position - this->_portal->position;
		float length = D3DXVec2Length(&distance);
		if (length <= this->_portal->height)
		{
			Teleport();
			DebugOut(L"[INFO] Collide with portal !\n");
		}
	}

	if (this->_isGrounded == false && (GetState() == MARIO_RUN || GetState() == MARIO_IDLE))
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
	this->_gui->Render();
}

void Mario::OnKeyDown(int keyCode)
{
	if (GetState() == MARIO_DEATH || this->_isActive == false)
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
		else if (GetState("figure") == MARIO_RACCOON && IsKeyDown(BTN_LEFT) == false && IsKeyDown(BTN_RIGHT) == false)
		{
			Attack();
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
	if (this->_isActive == false)
	{
		return;
	}
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
		if (GetState() == MARIO_SIT)
		{
			Idle();
		}
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
	if (GetState() == MARIO_DEATH || colEvent.collisionObj->isBlocking)
	{
		return;
	}

	string className = typeid(*colEvent.collisionObj).name();
	string name = colEvent.collisionObj->name;

	wstring wname = wstring(name.begin(), name.end());
	LPCWSTR pwname = wname.c_str();
	//DebugOut(L"[INFO] Mario collide with name:'%s'!\n", pwname);

	UINT t = GetState("touchable");
	
	if (className == "class Platform" && name != "portal in" && name != "portal out")
	{
		OnCollisionWithPlatform(colEvent);
	}
	else if (name == "portal in" || name == "portal out")
	{
		OnCollisionWithPortal(colEvent);
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
	_gui->IncreaseScore(score);
	DebugOut(L"[INFO] Increase Score!\n");
}

void Mario::IncreaseCoin(int coin)
{
	_gui->IncreaseCoin(coin);
}

void Mario::UpdateRunSpeed(float speed)
{
	_gui->UpdateRunSpeed(abs(speed));
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

	if (GetState("figure") == MARIO_RACCOON && GetState() == MARIO_JUMP && IsKeyDown(BTN_A))
	{
		aniName = "raccoon mario fall";
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

void Mario::HitByFire()
{
	if (GetState("touchable") == MARIO_UNTOUCHABLE)
	{
		return;
	}

	if (GetState("figure") != MARIO_SMALL)
	{
		ChangeFigure(MARIO_SMALL);
	}
	else
	{
		Death();
	}
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
	DebugOut(L"[MARIO] Idle !\n");
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
		DebugOut(L"[MARIO] Jump Run !\n");
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
	DebugOut(L"[MARIO] Run !\n");
}

void Mario::Jump(float speed)
{
	SetState(MARIO_JUMP);
	VECTOR2D vec = this->velocity;
	vec.y = speed;
	this->velocity = vec;
	this->acceleration = VECTOR2D(0.0f, 0.0f);
	DebugOut(L"[MARIO] Jump !\n");
}

void Mario::Fly()
{
	SetState(MARIO_FLY);
	this->_flyingTime = MARIO_FLYING_TIME;
	VECTOR2D vec = this->velocity;
	vec.y = MARIO_JUMP_SPEED_Y;
	this->velocity = vec;
	this->acceleration = VECTOR2D(0.0f, 0.0f);
	DebugOut(L"[MARIO] Fly !\n");
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
	DebugOut(L"[MARIO] Sit !\n");
}

void Mario::Death()
{
	SetState(MARIO_DEATH);
	this->velocity = VECTOR2D(0.0f, MARIO_JUMP_DEFLECT_SPEED);
	this->acceleration = VECTOR2D(0.0f, -MARIO_GRAVITY);
	DebugOut(L"[MARIO] Death !\n");
}

void Mario::Untouchable()
{
	DebugOut(L"[MARIO] Untouchable !\n");
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
	DebugOut(L"[MARIO] Hold !\n");
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
	DebugOut(L"[MARIO] Kick !\n");
}

void Mario::Attack()
{
	SetState(MARIO_ATTACK);
	this->_attackTime = MARIO_ATTACK_TIME;
	DebugOut(L"[MARIO] Attack !\n");
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
	}
}

void Mario::OnCollisionWithItem(CollisionEvent colEvent)
{
}

void Mario::OnCollisionWithGoomba(CollisionEvent colEvent)
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
		colEvent.collisionObj->isBlocking = true;
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
	if (GetState() == MARIO_ATTACK)
	{
		return;
	}
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
		colEvent.collisionObj->isBlocking = true;
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
		if (GetState() != MARIO_HOLD && IsKeyDown(BTN_B))
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

void Mario::OnCollisionWithPortal(CollisionEvent colEvent)
{
	this->_portal = colEvent.collisionObj;
}

bool Mario::IsKeyDown(int keyCode)
{
	KeyboardHandler* keyboard = KeyboardHandler::GetInstance();
	return keyboard->IsKeyDown(keyCode);
}

void Mario::Teleport()
{
	GameEngine* app = GameEngine::GetInstance();
	switch (GetState("scene"))
	{
	case SCENE_ONE_ID:
		if (this->_portal->name == "portal in" && IsKeyDown(BTN_DOWN))
		{
			app->TransitionTo(SCENE_HIDDEN_ID);
		}
		break;
	case SCENE_HIDDEN_ID:
		if (this->_portal->name == "portal out" && IsKeyDown(BTN_UP))
		{
			app->TransitionTo(SCENE_ONE_ID);
		}
		break;
	default:
		break;
	}
}
