#pragma once
#include "Sprite.h"
#include "../Utils/Property.h"

class AnimationFrame
{
public:
	AnimationFrame(Sprite* sprite, DWORD time);

#pragma region Properties
	R_PROPERTY(Sprite*, sprite);
	GET(sprite) { return this->_sprite; }
	
	R_PROPERTY(DWORD, time);
	GET(time) { return this->_time; }
#pragma endregion

private:
	Sprite* _sprite;
	DWORD _time;
};

