#pragma once
#include "../../Core/Scene.h"

#define SCENE_START "Assets/Tilemaps/world-map.json"
constexpr UINT SCENE_START_ID = 0;

class CSceneStart: public Scene
{
public:
	CSceneStart();
	void Update(float deltaTime) override;
	void OnChanged(UINT preSceneId) override;
	void Render() override;

private:
	Sprite* _background;
};

