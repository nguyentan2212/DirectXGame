#pragma once
#include "../../Core/Scene.h"

class CSceneOne: public Scene
{
public:
	CSceneOne(string configPath);
	void InitObjects(json config) override;
};

