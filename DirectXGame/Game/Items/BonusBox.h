#pragma once
#include "../../Core/GameObject.h"

constexpr float BONUS_BOX_SIZE = 26;
constexpr float BONUS_BOX_SPEED = 50;
constexpr float BONUS_BOX_DURATION = 2000;

constexpr UINT UNTOUCHED = 0;
constexpr UINT TOUCHED = 1;
class BonusBox: public GameObject
{
public:
	BonusBox();
	void Update(float deltaTime) override;
	void OnCollision(CollisionEvent colEvent) override;
	void Render() override;

private:
	GameObject* _content;
	float _duration = BONUS_BOX_DURATION;

	Renderable* GetRenderable() override;
};

