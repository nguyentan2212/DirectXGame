#pragma once
#include <d3d10.h>
#include <D3DX10.h>
#include "Texture.h"
#include "Renderable.h"
#include "../Utils/Property.h"
#include "../Utils/CMath.h"

class Sprite: public Renderable
{
public:
    Sprite(float x, float y, float width, float height, Texture* texture);
    ~Sprite();

    void Render(float x, float y, bool isFlipped = false, float zIndex = 0.0f) override;
    void Render(VECTOR2D position, bool isFlipped = false, float zIndex = 0.0f) override;

#pragma region Properties
    R_PROPERTY(float, width);
    GET(width) { return this->_width; }

    R_PROPERTY(float, height);
    GET(height) { return this->_height; }
#pragma endregion

private:
    float _x;
    float _y;
    float _width;
    float _height;

    Texture* _texture;
    D3DX10_SPRITE _sprite;
    MATRIX _matScaling;
};

