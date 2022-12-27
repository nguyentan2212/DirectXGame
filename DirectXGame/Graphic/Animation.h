#pragma once
#include <vector>
#include <string>
#include "AnimationFrame.h"
#include "Sprite.h"

using namespace::std;

class Animation
{
public:
	Animation(DWORD defaultTime = 100);

	void AddFrame(string spriteName, DWORD time = 0);
	void AddFrame(Sprite* sprite, DWORD time = 0);

	void Update(float deltaTime);
	void Render(float x, float y, bool isFlipped = false, float zIndex = 0.0f);
	void Render(VECTOR2D position, bool isFlipped = false, float zIndex = 0.0f);

private:
	DWORD _defaultTime;
	int _currentFrame;
	float _totalDelayTime;
	vector<AnimationFrame*> _frames;
};

