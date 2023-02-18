#pragma once
#include "../../Core/GameObject.h"

constexpr float FIRE_TRAP_WIDTH = 16;
constexpr float FIRE_TRAP_HEIGHT = 32;

// attack
constexpr float FIRE_TRAP_Y_SPEED = 30;
constexpr float FIRE_TRAP_X_DISTANCE_DETECT = 80;
constexpr float FIRE_TRAP_ATTACK_COOLDOWN = 2500;
constexpr float FIRE_BALL_SPEED = 50;
constexpr float FIRE_BALL_MAX_DISTANCE = 600;

// state
constexpr UINT FIRE_TRAP_SLEEP = 0;
constexpr UINT FIRE_TRAP_AWAKE = 1;
constexpr UINT FIRE_TRAP_ATTACK = 2;
constexpr UINT FIRE_TRAP_DEATH = 3;

// figure
constexpr UINT FIRE_TRAP_RED = 0;
constexpr UINT FIRE_TRAP_GREEN = 1;

class VenusFireTrap: public GameObject
{
public:
	VenusFireTrap(VECTOR2D sleepPos, string name = "red venus fire trap");

	void Render() override;
	void Update(float deltaTime) override;
	void OnCollision(CollisionEvent colEvent) override;
	void SetState(UINT stateValue, string stateName = "default") override;

private:
	Renderable* GetRenderable() override;

	VECTOR2D _sleepPosition;
	bool DetectTarget();

	void Sleep();
	void Attack();
	void Awake();

	GameObject* _attackTarget = nullptr;
	float _cooldown = FIRE_TRAP_ATTACK_COOLDOWN;
};

