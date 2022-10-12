#pragma once
#include <d3d10.h>
#include <D3DX10.h>
#include "Texture.h"
#include "../Utils/CMath.h"

class Sprite
{
public:
    Sprite(float x, float y, float width, float height, Texture* texture);
    ~Sprite();

    void Draw(float x, float y, bool isFlipped = false);
    void Draw(VECTOR2D position, bool isFlipped = false);
    RECT GetBounderBox();

private:
    float _x;
    float _y;
    float _width;
    float _height;

    Texture* _texture;
    D3DX10_SPRITE _sprite;
    MATRIX _matScaling;
};
