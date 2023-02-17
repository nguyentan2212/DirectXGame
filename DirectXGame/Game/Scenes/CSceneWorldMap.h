#pragma once
#include "../../Core/Scene.h"

#define SCENE_WORLD_MAP "Assets/Tilemaps/world-map.json"

constexpr UINT SCENE_WORLD_MAP_ID = 1;
class CSceneWorldMap: public Scene
{
public:
	CSceneWorldMap();
	void Update(float deltaTime) override;
	void OnChanged(UINT preSceneId) override;
};

