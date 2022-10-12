#pragma once
#include <D3DX10.h>

#define VECTOR D3DXVECTOR4
#define VECTOR2D D3DXVECTOR2

#define MATRIX D3DXMATRIX

#define DIRECTION Direction

enum Direction 
{
	UP,
	DOWN,
	LEFT,
	RIGHT,
	NONE
};