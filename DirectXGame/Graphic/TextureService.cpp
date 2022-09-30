#include "TextureService.h"
#include "Graphic.h"
#include "../Utils/Debug.h"

TextureService* TextureService::_instance = nullptr;

TextureService::TextureService()
{
    
}

TextureService* TextureService::GetInstance()
{
    if (_instance == nullptr)
    {
        _instance = new TextureService();
    }
    return _instance;
}

void TextureService::Init(json config)
{
    Graphic* graphic = Graphic::GetInstance();

    for (json item : config)
    {
        string name = item["name"].get<string>();

        string sSpritePath = item["spritePath"].get<string>();
        wstring wSpritePath = wstring(sSpritePath.begin(), sSpritePath.end());
        LPCWSTR spritePath = wSpritePath.c_str();

        string simage = item["image"].get<string>();
        wstring wimage = wstring(simage.begin(), simage.end());
        LPCWSTR image = wimage.c_str();

        this->_textures[name] = graphic->CreateTexture(image);
    }
}
