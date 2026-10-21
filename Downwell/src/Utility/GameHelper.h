#pragma once

struct Color
{
	int r;
	int g;
	int b;
};
constexpr Color WHITE{ 255, 255, 255 };
constexpr Color RED{ 255, 0, 0 };
constexpr Color GREEN{ 0, 255, 0 };
constexpr Color BLUE{ 0, 0, 255 };
constexpr Color YELLOW{ 255, 255, 0 };
constexpr Color PURPLE{ 255, 0, 255 };
constexpr Color GRAY{ 120, 120, 120 };

constexpr int WINDOW_WIDTH = 1280;
constexpr int WINDOW_HEIGHT = 720;

constexpr int MAP_SIZE_Y = 40;
constexpr int MAP_SIZE_X = 11;
constexpr float TILE_SIZE = 47.0f;

constexpr int STAGE_SECTION_COUNT = 7;
constexpr int MIDDLE_SECTION_COUNT = STAGE_SECTION_COUNT - 2;//スタートとゴールを除いた数
constexpr int MIDDLE_MAP_ALL = 10;

constexpr float STAGE_LEFT = ((static_cast<float>(WINDOW_WIDTH) * 0.5f) - (static_cast<float>(MAP_SIZE_X - 1) * TILE_SIZE * 0.5f));
constexpr float STAGE_RIGHT = 1280;