#pragma once
#include <d3d10.h>
#include <D3DX10.h>
#include "Texture.h"

class Sprite
{
public:
    Sprite(float x, float y, float width, float height, Texture* texture);
    ~Sprite();

    void Draw(float x, float y);
    RECT GetBounderBox();

private:
    float _x;
    float _y;
    float _width;
    float _height;

    Texture* _texture;
    D3DX10_SPRITE _sprite;
    D3DXMATRIX _matScaling;
};

