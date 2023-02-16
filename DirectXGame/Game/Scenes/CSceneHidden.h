#pragma once
#include "../../Core/Scene.h"

#define SCENE_HIDDEN "Assets/Tilemaps/hidden-map.json"
constexpr UINT SCENE_HIDDEN_ID = 3;

class CSceneHidden: public Scene
{
public:
	CSceneHidden();
	void InitObjects(json config) override;
	void Update(float deltaTime) override;
	void OnChanged() override;
};

