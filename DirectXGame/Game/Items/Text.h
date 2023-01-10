#pragma once
#include "../../Core/GameObject.h"

constexpr float SCORE_MAX_HEIGHT = 80.0f;
constexpr float SCORE_SPEED = 120.0f;

class Text: public GameObject
{
public:
	Text(Sprite* sprite, float beginY);
	void Update(float deltaTime) override;
	void Render() override;

private:
	Sprite* _sprite;
	float _beginY;
};

