#include "Animation.h"
#include "SpriteService.h"
#include "../Utils/Debug.h"

Animation::Animation(DWORD defaultTime)
{
	this->_defaultTime = defaultTime;
	this->_currentFrame = 0;
	this->_totalDelayTime = 0;
}

void Animation::AddFrame(string spriteName, DWORD time)
{
	SpriteService* sprites = SpriteService::GetInstance();
	Sprite* sprite = sprites->GetSprite(spriteName);
	AddFrame(sprite, time);
}

void Animation::AddFrame(Sprite* sprite, DWORD time)
{
	time = time > 0 ? time : this->_defaultTime;

	AnimationFrame* frame = new AnimationFrame(sprite, time);

	this->_frames.push_back(frame);
}

void Animation::Update(float deltaTime)
{
	this->_totalDelayTime += deltaTime;

	DWORD time = this->_frames[this->_currentFrame]->time;
	if (this->_totalDelayTime > time)
	{
		this->_totalDelayTime = 0.0f;
		this->_currentFrame = (this->_currentFrame + 1) % this->_frames.size();
	}
}

void Animation::Render(VECTOR2D position, bool isFlipped)
{
	Render(position.x, position.y, isFlipped);
}

void Animation::Render(float x, float y, bool isFlipped)
{
	this->_frames[this->_currentFrame]->sprite->Draw(x, y, isFlipped);
}
