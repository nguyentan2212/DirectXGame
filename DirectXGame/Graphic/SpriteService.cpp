
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
	for (json item : config)
	{
		string textureName = item["name"].get<string>();
		string textureType = item["type"].get<string>();
		string spritePath = item["spritePath"].get<string>();
		fstream file(spritePath);
		json textureJson = json::parse(file);
		if (textureType == "spritesheet")
		{
			InitSpriteSheet(textureName, textureJson);
		}
		else
		{
			InitTileset(textureName, textureJson);
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
	return GetSprite(textureName + to_string(index));
}

SpriteService::~SpriteService()
{
}

void SpriteService::InitSpriteSheet(string textureName, json config)
{
	json sprites = config["sprites"];
	TextureService* textures = TextureService::GetInstance();
	Texture* texture = textures->GetTexture(textureName);

	for (json sprite : sprites)
	{
		string name = sprite["name"].get<string>();
		float x = sprite["frame"]["x"].get<float>();
		float y = sprite["frame"]["y"].get<float>();
		float w = sprite["frame"]["w"].get<float>();
		float h = sprite["frame"]["h"].get<float>();

		Sprite* pSprite = new Sprite(x, y, w, h, texture);
		this->_sprites[name] = pSprite;

		wstring wname = wstring(name.begin(), name.end());
		LPCWSTR pwname = wname.c_str();
		DebugOut(L"[INFO] Sprite name:'%s' load success !\n", pwname);
	}
}

void SpriteService::InitTileset(string textureName, json config)
{
	TextureService* textures = TextureService::GetInstance();
	Texture* texture = textures->GetTexture(textureName);

	int columns = config["columns"];
	int imageHeight = config["imageheight"];
	int imagewidth = config["imagewidth"];
	int margin = config["margin"];
	int spacing = config["spacing"];
	int tileCount = config["tilecount"];
	int tileHeight = config["tileheight"];
	int tileWidth = config["tilewidth"];

	for (int i = 0; i < tileCount; i++)
	{
		string spriteName = textureName + to_string(i);
		int col = i % columns;
		int row = i / columns;
		int x = col * tileWidth + col * spacing + margin;
		int y = row * tileHeight + row * spacing + margin;
		Sprite* sprite = new Sprite((float)x, (float)y, (float)tileWidth, (float)tileHeight, texture);
		this->_sprites[spriteName] = sprite;

		wstring wname = wstring(spriteName.begin(), spriteName.end());
		LPCWSTR pwname = wname.c_str();
		DebugOut(L"[INFO] Sprite name:'%s' load success !\n", pwname);
	}
}
