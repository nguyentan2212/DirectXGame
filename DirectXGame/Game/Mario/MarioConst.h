#pragma once
#include <string>
#include <utility>
constexpr float MARIO_GRAVITY = 120;

constexpr float MARIO_X_ACCE = 80;
constexpr float MARIO_RUN_MAX_SPEED_X = 120;
constexpr float MARIO_JUMP_SPEED_Y = 100;
constexpr float MARIO_SUPER_JUMP_Y = 135;
constexpr float MARIO_RUN_JUMP_SPEED_FACTOR_Y = 1.35f;
constexpr float MARIO_JUMP_DEFLECT_SPEED = 400;
constexpr float MARIO_SIT_HEIGHT = 18.0f;

constexpr float MARIO_SMALL_HEIGHT = 16.0f;
constexpr float MARIO_SMALL_WIDTH = 16.0f;

constexpr float MARIO_SUPER_HEIGHT = 28.0f;
constexpr float MARIO_SUPER_WIDTH = 16.0f;

constexpr float MARIO_RACCOON_HEIGHT = 28.0f;
constexpr float MARIO_RACCOON_WIDTH = 23.0f;

// figure state
constexpr UINT MARIO_SMALL = 0;
constexpr UINT MARIO_SUPER = 1;
constexpr UINT MARIO_RACCOON = 2;

// default state
constexpr UINT MARIO_IDLE = 0;
constexpr UINT MARIO_RUN = 1;
constexpr UINT MARIO_JUMP = 2;
constexpr UINT MARIO_FALL = 3;
constexpr UINT MARIO_FLY = 4;
constexpr UINT MARIO_SIT = 5;
constexpr UINT MARIO_DEATH = 6;
constexpr UINT MARIO_UNTOUCHABLE = 7;

const std::string aniNames[8] = {
	"idle",
	"run",
	"jump",
	"fall",
	"fly",
	"sit",
	"death",
	"untouchable",
};

const std::string figureNames[3] = {
	"small mario",
	"super mario",
	"raccoon mario",
};

// first == width, second == height
const std::pair<float, float> mario_sizes[3] = {
	{16.0f, 16.0f}, // small
	{16.0f, 28.0f}, // super
	{23.0f, 28.0f}, // raccoon
};

