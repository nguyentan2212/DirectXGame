#pragma once
#include <D3DX10.h>

#define VECTOR D3DXVECTOR4
#define VECTOR2D D3DXVECTOR2
#define MATRIX D3DXMATRIX

enum Direction 
{
	UP,
	DOWN,
	LEFT,
	RIGHT,
	NONE
};
#define DIRECTION Direction

struct Box
{
	float x;
	float y;
	float width;
	float height;

	Box()
	{
		x = y = width = height = 0.0f;
	}

	Box(float x, float y, float width, float height)
	{
		this->x = x;
		this->y = y;
		this->width = width;
		this->height = height;
	}
};