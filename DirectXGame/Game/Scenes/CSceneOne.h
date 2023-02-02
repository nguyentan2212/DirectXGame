#pragma once
#include "../../Core/Scene.h"

#define SCENE_ONE "Assets/Tilemaps/stage-1.json"

class CSceneOne: public Scene
{
public:
	CSceneOne();
	void InitObjects(json config) override;
	void Update(float deltaTime) override;

private:
	void CreateMario(VECTOR2D position);
};

