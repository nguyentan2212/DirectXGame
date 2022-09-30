#pragma once
#include <map>
#include <string>
#include "Texture.h"
#include "../Utils/json.hpp"

using namespace::std;
using json = nlohmann::json;

class TextureService
{
public:
	static TextureService* GetInstance();
	void Init(json config);

private:
	TextureService();
	map<string, Texture*> _textures;

	static TextureService* _instance;
};

