#pragma once
#include "../../Core/Scene.h"

#define SCENE_WORLD_MAP "Assets/Tilemaps/world-map.json"

class CSceneWorldMap: public Scene
{
public:
	CSceneWorldMap();
	void Update(float deltaTime) override;
};

