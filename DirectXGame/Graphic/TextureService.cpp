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

        string simage = item["image"].get<string>();
        wstring wimage = wstring(simage.begin(), simage.end());
        LPCWSTR image = wimage.c_str();

        this->_textures[name] = graphic->CreateTexture(image);
    }
}

Texture* TextureService::GetTexture(string name)
{
    Texture* texture = this->_textures[name];
    if (texture == nullptr)
    {
        DebugOut(L"[ERROR] Texture name: '%s' not found !\n", name);
    }
    return texture;
}
