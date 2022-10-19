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
	map<string, Sprite*> _sprites;
	map<string, Sprite*> _spritesById;

	static SpriteService* _instance;
};
