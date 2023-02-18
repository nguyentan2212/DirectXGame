#pragma once
#include "../../Core/GameObject.h"
#include "../Items/Head.h"

constexpr float PARAGOOMBA_SPEED_X = 15.0f;
constexpr float PARAGOOMBA_WIDTH = 16.0;
constexpr float PARAGOOMBA_HEIGHT = 16.0;
constexpr float PARAGOOMBA_DEATH_HEIGHT = 9.0;
constexpr float PARAGOOMBA_GRAVITY = 100.0;
constexpr float PARAGOOMBA_JUMP_SPEED = 40.0;
constexpr float PARAGOOMBA_SUPER_JUMP_SPEED = 70.0;
constexpr float PARAGOOMBA_DEATH_DURATION = 1500;
constexpr float PARAGOOMBA_RUN_DURATION = 3000;
constexpr float PARAGOOMBA_SCORE_DURATION = 1500;
constexpr float PARAGOOMBA_JUMP_DEFLECT_SPEED = 60;
constexpr float PARAGOOMBA_REMOVE_HEAD_DISTANCE = 200;
// state
constexpr UINT PARAGOOMBA_HAS_WING = 0;
constexpr UINT PARAGOOMBA_LOST_WING = 1;
constexpr UINT PARAGOOMBA_DEATH_BY_JUMP = 2;
constexpr UINT PARAGOOMBA_DEATH_BY_ATTACK = 3;

constexpr UINT SCORE_PARAGOOMBA_LOST_WING = 400;
constexpr UINT SCORE_PARAGOOMBA_DEATH = 800;

class ParaGoomba: public GameObject
{
public:
	ParaGoomba();

	void Render() override;
	void Update(float deltaTime) override;
	void OnCollision(CollisionEvent colEvent) override;
	void SetState(UINT stateValue, string stateName = "default") override;
private:
	Renderable* GetRenderable() override;

	GameObject* _score = nullptr;
	GameObject* _leftWing = nullptr;
	GameObject* _rightWing = nullptr;
	Head* _head;

	int _jumpCount = 0;
	float _deathDuration = PARAGOOMBA_DEATH_DURATION;
	float _runDuration = PARAGOOMBA_RUN_DURATION;
	float _scoreDuration = PARAGOOMBA_SCORE_DURATION;
	float _gravity = PARAGOOMBA_GRAVITY;
	void Jump(float speed);
	void Death();
};

