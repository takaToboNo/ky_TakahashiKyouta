#pragma once

struct Color
{
	int r;
	int g;
	int b;
};
constexpr Color WHITE{ 255, 255, 255 };
constexpr Color RED{ 255, 0, 0 };
constexpr Color YELLOW{ 255, 255, 0 };
constexpr Color GRAY{ 120, 120, 120 };

//ゲーム色
constexpr Color PLAYER_IDLE_COLOR{ 255, 255, 255 };
constexpr Color PLAYER_MOVE_COLOR{ 100, 220, 200 };
constexpr Color PLAYER_JUMP_COLOR{ 140, 200, 255 };
constexpr Color PLAYER_FALL_COLOR{ 170, 160, 255 };
constexpr Color PLAYER_SHOT_COLOR{ 255, 220, 140 };
constexpr Color PLAYER_DEAD_COLOR{ 150, 150, 150 };
constexpr Color BLOCK_COLOR{ 220, 220, 220 };
constexpr Color ENEMY_COLOR{ 255, 50, 50 };
//デバッグ色
constexpr Color DEBUG_COUNT_COLOR{ 255,230,150 };
constexpr Color DEBUG_STATUS_COLOR{ 120,200,255 };
constexpr Color DEBUG_NORMAL_COLOR{ 120,120,120 };

constexpr int MAX_UPDATE = 3;

constexpr int WINDOW_WIDTH = 1280;
constexpr int WINDOW_HEIGHT = 720;

constexpr int MAP_SIZE_Y = 40;
constexpr int MAP_SIZE_X = 11;
constexpr float TILE_SIZE = 47.0f;

constexpr int STAGE_SECTION_COUNT = 7;
constexpr int MIDDLE_SECTION_COUNT = STAGE_SECTION_COUNT - 2;//スタートとゴールを除いた数
constexpr int MIDDLE_MAP_ALL = 10;

constexpr float STAGE_LEFT = ((static_cast<float>(WINDOW_WIDTH) * 0.5f) - (static_cast<float>(MAP_SIZE_X - 1) * TILE_SIZE * 0.5f));
constexpr float STAGE_RIGHT = ((static_cast<float>(WINDOW_WIDTH) * 0.5f) + (static_cast<float>(MAP_SIZE_X - 1) * TILE_SIZE * 0.5f));

constexpr int MAX_AMMO = 10;