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

constexpr float STAGE_TOP = 0;
constexpr float STAGE_BOTTOM = 700;//‰¼
constexpr float STAGE_LEFT = 0;
constexpr float STAGE_RIGHT = 1280;