#pragma once
#include <string>
#include <utility>
#include <dinput.h>

constexpr float MARIO_GRAVITY =					120;
constexpr float MARIO_WEEK_GRAVITY =			70;
constexpr float MARIO_EXTRA_WEEK_GRAVITY =		50;


constexpr float F_LEFT =						-1;
constexpr float F_RIGHT =						1;

constexpr float KICK_TIME =						300.0f;
constexpr float UNTOUCHABLE_TIME =				1000.0f;
constexpr float MARIO_FLYING_TIME =				4000.0f;
constexpr float MARIO_ATTACK_TIME =				600.0f;

constexpr float MARIO_RUN_LOW_SPEED =			60;
constexpr float MARIO_X_ACCE =					80;
constexpr float MARIO_RUN_MAX_SPEED_X =			110;
constexpr float MARIO_JUMP_SPEED_Y =			100;
constexpr float MARIO_SUPER_JUMP_Y =			135;
constexpr float MARIO_JUMP_DEFLECT_SPEED =		130;

constexpr float MARIO_SIT_HEIGHT =				18.0f;

constexpr float MARIO_SMALL_HEIGHT =			16.0f;
constexpr float MARIO_SMALL_WIDTH =				16.0f;

constexpr float MARIO_SUPER_HEIGHT =			28.0f;
constexpr float MARIO_SUPER_WIDTH =				16.0f;

constexpr float MARIO_RACCOON_HEIGHT =			28.0f;
constexpr float MARIO_RACCOON_WIDTH =			23.0f;

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
constexpr UINT MARIO_KICK = 7;
constexpr UINT MARIO_ATTACK = 8;

// hold state
constexpr UINT MARIO_HOLD = 0;
constexpr UINT MARIO_NOT_HOLD = 1;

// touchable state
constexpr UINT MARIO_UNTOUCHABLE = 0;
constexpr UINT MARIO_TOUCHABLE = 1;

const std::string aniNames[9] = {
	"idle",
	"run",
	"jump",
	"fall",
	"fly",
	"sit",
	"death",
	"kick",
	"attack",
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

#define BTN_UP		DIK_W
#define BTN_DOWN	DIK_S
#define BTN_LEFT	DIK_A
#define BTN_RIGHT	DIK_D
#define BTN_A		DIK_K
#define BTN_B		DIK_L

constexpr UINT SCORE_GOOMBA_DEATH =			100;
constexpr UINT SCORE_PARAGOOMBA_LOST_WING = 400;
constexpr UINT SCORE_PARAGOOMBA_DEATH =		800;

constexpr UINT SCORE_COIN_BRICK = 200;
constexpr UINT SCORE_POWER_MUSHROOM = 1000;
constexpr UINT SCORE_LEAF = 1000;