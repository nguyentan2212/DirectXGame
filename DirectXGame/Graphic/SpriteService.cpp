
#include <fstream>
#include "SpriteService.h"
#include "../Utils/Debug.h"
#include "TextureService.h"

SpriteService* SpriteService::_instance = nullptr;

SpriteService::SpriteService()
{

}

SpriteService* SpriteService::GetInstance()
{
	if (_instance == nullptr)
	{
		_instance = new SpriteService();
	}
	return _instance;
}

void SpriteService::Init(json config)
{
	TextureService* textures = TextureService::GetInstance();

	for (json item : config)
	{
		string textureName = item["name"].get<string>();
		Texture* texture = textures->GetTexture(textureName);
		int count = 0;

		string spritePath = item["spritePath"].get<string>();
		fstream file(spritePath);
		json spriteJson = json::parse(file);
		json sprites = spriteJson["sprites"];
		for (json sprite : sprites)
		{
			string name = sprite["name"].get<string>();
			float x = sprite["frame"]["x"].get<float>();
			float y = sprite["frame"]["y"].get<float>();
			float w = sprite["frame"]["w"].get<float>();
			float h = sprite["frame"]["h"].get<float>();
			
			Sprite* pSprite = new Sprite(x, y, w, h, texture);
			this->_sprites[name] = pSprite;
			this->_spritesById[textureName + to_string(count)] = pSprite;

			wstring wname = wstring(name.begin(), name.end());
			LPCWSTR pwname = wname.c_str();
			DebugOut(L"[INFO] Sprite name:'%s' load success !\n", pwname);
			count++;
		}
	}
}

Sprite* SpriteService::GetSprite(string name)
{
	Sprite* sprite = this->_sprites[name];
	if (sprite == nullptr)
	{
		DebugOut(L"[ERROR] Sprite name: '%s' not found !\n", name);
	}
	return sprite;
}

Sprite* SpriteService::GetSprite(string textureName, int index)
{
	Sprite* sprite = this->_spritesById[textureName + to_string(index)];
	if (sprite == nullptr)
	{
		DebugOut(L"[ERROR] Sprite id: '%s%d' not found !\n", textureName, index);
	}
	return sprite;
}

SpriteService::~SpriteService()
{
}
