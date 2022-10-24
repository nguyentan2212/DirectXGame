#pragma once
#include <map>
#include <string>
#include "Sprite.h"
#include "../Utils/json.hpp"

using namespace::std;
using json = nlohmann::json;

class SpriteService
{
public:
	static SpriteService* GetInstance();
	
	void Init(json config);
	Sprite* GetSprite(string name);
	Sprite* GetSprite(string textureName, int index);

private:
	SpriteService();
	~SpriteService();
	void InitSpriteSheet(string textureName, json config);
	void InitTileset(string textureName, json config);
	map<string, Sprite*> _sprites;

	static SpriteService* _instance;
};
