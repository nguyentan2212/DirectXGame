#include "GUI.h"
#include "../Core/Camera.h"
#include "../Graphic/SpriteService.h"
#include <string> 
#include "Mario/Mario.h"

GUI::GUI(): GameObject(new ObjectState())
{
	this->_name = "gui";
}

void GUI::Update(float deltaTime)
{
	this->_totalTime += deltaTime / 1000;
	this->_time = floor(this->_totalTime);
	AnimationService* anis = AnimationService::GetInstance();
	Animation* ani = anis->GetAnimation("mario max speed");
	ani->Update(deltaTime);
}

void GUI::Render()
{
	SpriteService* sprites = SpriteService::GetInstance();

	// render hub
	Sprite* sprite = sprites->GetSprite("hub-and-font/hub");
	VECTOR2D pos = VECTOR2D(sprite->width / 2 + 5.0f, sprite->height / 2);
	sprite->Render(pos.x + 5.0f, pos.y, false, 0.1f);

	// render world index
	sprite = sprites->GetSprite("hub-and-font/1");
	sprite->Render(pos.x - 30.0f, pos.y + 3.0f);

	// render life point
	sprite = sprites->GetSprite("hub-and-font/label-m");
	sprite->Render(pos.x - 59.0f, pos.y - 5.0f);

	sprite = sprites->GetSprite("hub-and-font/" + std::to_string(this->_lifePoint));
	sprite->Render(pos.x - 30.0f, pos.y - 5.0f);

	// render score
	std::string scoreStr = std::to_string(this->_score);
	while (scoreStr.length() < 7)
	{
		scoreStr = "0" + scoreStr;
	}
	for (int i = 0; i < scoreStr.length(); i++)
	{
		std::string s = "hub-and-font/";
		s.push_back(scoreStr[i]);
		sprite = sprites->GetSprite(s);
		sprite->Render(pos.x + i * sprite->width - 15.0f, pos.y - 6.0f);
	}

	// render acce bar
	int whiteAcc = this->_speed != 0 ? (int)floor(this->_speed / MARIO_RUN_MAX_SPEED_X * 6.0f) : 0;

	sprite = sprites->GetSprite("hub-and-font/arrow-white");
	for (int i = 0; i < whiteAcc; i++)
	{
		sprite->Render(pos.x + i * sprite->width - 15.0f, pos.y + 2.0f);
	}
	sprite = sprites->GetSprite("hub-and-font/arrow-black");
	for (int i = whiteAcc; i < 6; i++)
	{
		sprite->Render(pos.x + i * sprite->width - 15.0f, pos.y + 2.0f);
	}

	if (whiteAcc == 6)
	{
		AnimationService* anis = AnimationService::GetInstance();
		Animation* ani = anis->GetAnimation("mario max speed");
		ani->Render(pos.x + 38.0f, pos.y + 2.0f);
	}
	else
	{
		sprite = sprites->GetSprite("hub-and-font/label-f-black");
		sprite->Render(pos.x + 38.0f, pos.y + 2.0f);
	}
	
	// render money
	if (this->_money > 10)
	{
		sprite = sprites->GetSprite("hub-and-font/" + std::to_string(this->_money / 10));
		sprite->Render(pos.x + 65.0f, pos.y + 3.0f);
	}

	sprite = sprites->GetSprite("hub-and-font/" + std::to_string(this->_money % 10));
	sprite->Render(pos.x + 73.0f, pos.y + 3.0f);

	// render time
	std::string timeStr = std::to_string(this->_time);
	while (timeStr.length() < 3)
	{
		timeStr = "0" + timeStr;
	}
	for (int i = 0; i < timeStr.length(); i++)
	{
		std::string s = "hub-and-font/";
		s.push_back(timeStr[i]);
		sprite = sprites->GetSprite(s);
		sprite->Render(pos.x + i * 8.0 + 57.0f, pos.y - 6.0f);
	}
	// render three squares
	pos.x = pos.x * 2.0f + 3.0;
	sprite = sprites->GetSprite("hub-and-font/empty");
	for (int i = 0; i < 3; i++)
	{
		pos.x += sprite->width;
		sprite->Render(pos.x, pos.y);
	}
}

void GUI::IncreaseScore(int score)
{
	this->_score += score;
}

void GUI::IncreaseCoin(int coin)
{
	this->_money += coin;
}

void GUI::UpdateRunSpeed(float speed)
{
	this->_speed = speed;
}
