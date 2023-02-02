#pragma once
#include "../../Core/GameObject.h"

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
// state
constexpr UINT PARAGOOMBA_HAS_WING = 0;
constexpr UINT PARAGOOMBA_LOST_WING = 1;
constexpr UINT PARAGOOMBA_DEATH = 2;

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

	int _jumpCount = 0;
	float _deathDuration = PARAGOOMBA_DEATH_DURATION;
	float _runDuration = PARAGOOMBA_RUN_DURATION;
	float _scoreDuration = PARAGOOMBA_SCORE_DURATION;

	void Jump(float speed);
	void Death();
};

