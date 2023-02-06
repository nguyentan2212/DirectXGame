#pragma once
#include <map>
#include <string>
#include "Animation.h"
#include "../Utils/json.hpp"

using namespace::std;
using json = nlohmann::json;

class AnimationService
{
public:
	static AnimationService* GetInstance();

	void Init(json config);
	void Update(float deltaTime);
	Animation* GetAnimation(string name);

private:
	AnimationService();
	~AnimationService();
	map<string, Animation*> _animations;

	static AnimationService* _instance;
};

