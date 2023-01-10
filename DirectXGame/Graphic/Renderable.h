#pragma once
#include "../Utils/CMath.h"

class Renderable
{
public:
	Renderable() {};
	
	virtual void Update(float deltaTime) {};
	virtual void Render(float x, float y, bool isFlipped = false, float zIndex = 0.0f) = 0;
	virtual void Render(VECTOR2D position, bool isFlipped = false, float zIndex = 0.0f) = 0;
};
