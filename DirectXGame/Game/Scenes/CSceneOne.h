#pragma once
#include "../../Core/Scene.h"

#define SCENE_ONE "Assets/Tilemaps/stage-1.json"

constexpr UINT SCENE_ONE_ID = 2;
class CSceneOne: public Scene
{
public:
	CSceneOne();
	void InitObjects(json config) override;
	void Update(float deltaTime) override;
	void OnChanged(UINT preSceneId) override;

private:
	void CreateMario(VECTOR2D position);
};

