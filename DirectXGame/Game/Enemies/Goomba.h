#pragma once
#include "../../Core/GameObject.h"

constexpr float GOOMBA_SPEED = 30;
constexpr float GOOMBA_GRAVITY = 120;
constexpr float GOOMBA_SIZE = 16;
constexpr float GOOMBA_DEATH_HEIGHT = 9;
constexpr float GOOMBA_DEATH_DURATION = 1500;
constexpr float GOOMBA_SCORE_SPEED = 40;
constexpr float GOOMBA_JUMP_DEFLECT_SPEED = 60;

constexpr UINT GOOMBA_WALK = 0;
constexpr UINT GOOMBA_DEATH_BY_JUMP = 1;
constexpr UINT GOOMBA_DEATH_BY_ATTACK = 2;

class Goomba: public GameObject
{
public:
	Goomba();
	void Update(float deltaTime) override;
	void OnCollision(CollisionEvent colEvent) override;
	void SetState(UINT stateValue, string stateName = "default") override;

private:
	Renderable* GetRenderable() override;
	float _deathDuration = GOOMBA_DEATH_DURATION;
	GameObject* _score;
	float _gravity = GOOMBA_GRAVITY;
	void Death();
};