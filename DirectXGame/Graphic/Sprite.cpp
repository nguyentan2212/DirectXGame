#include "Sprite.h"
#include "Graphic.h"

Sprite::Sprite(float x, float y, float width, float height, Texture* texture)
{
    this->_x = x;
    this->_y = y;
    this->_width = width;
    this->_height = height;
    this->_texture = texture;

    float textureWidth = (float)texture->width;
    float textureHeight = (float)texture->height;

    // Set the sprite’s shader resource view
    this->_sprite.pTexture = texture->shaderRsView;

    this->_sprite.TexCoord.x = x / textureWidth;
    this->_sprite.TexCoord.y = y / textureHeight;

    this->_sprite.TexSize.x = width / textureWidth;
    this->_sprite.TexSize.y = height / textureHeight;

    this->_sprite.ColorModulate = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
    this->_sprite.TextureIndex = 0;

    D3DXMatrixScaling(&this->_matScaling, (float)width, (float)height * -1.0f, 1.0f);
}

Sprite::~Sprite()
{
    if (this->_texture != nullptr)
    {
        delete this->_texture;
    }
}

void Sprite::Draw(float x, float y, bool isFlipped)
{
    MATRIX matTranslation;

    x = (FLOAT)floor(x);
    y = (FLOAT)floor(y);

    Graphic* graphic = Graphic::GetInstance();
    D3DXMatrixTranslation(&matTranslation, x, graphic->backBufferHeight - y, 0.1f);

    MATRIX matScaling = this->_matScaling;
    if (isFlipped)
    {
        D3DXMatrixScaling(&matScaling, (float)this->_width * -1.0f, (float)this->_height * -1.0f, 1.0f);
    }

    this->_sprite.matWorld = matScaling * matTranslation;
    graphic->spriteHandler->DrawSpritesImmediate(&this->_sprite, 1, 0, 0);
}

void Sprite::Draw(VECTOR2D position, bool isFlipped)
{
    Draw(position.x, position.y, isFlipped);
}

RECT Sprite::GetBounderBox()
{
    RECT rect = RECT();
    rect.left = (long)this->_x;
    rect.top = (long)this->_y;
    rect.right = rect.left + (long)this->_width;
    rect.bottom = rect.top + (long)this->_height;
    return rect;
}
