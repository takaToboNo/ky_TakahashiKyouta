#pragma once

struct Color
{
	int r;
	int g;
	int b;
};
constexpr Color kWhite{ 255, 255, 255 };
constexpr Color kRed{ 255, 0, 0 };
constexpr Color kGreen{ 0, 255, 0 };
constexpr Color kBlue{ 0, 0, 255 };
constexpr Color kYellow{ 255, 255, 0 };

constexpr int kScreenWidth = 1280;
constexpr int kScreenHeight = 720;

constexpr float kStageTop = 0;
constexpr float kStageBottom = 700;//‰¼
constexpr float kStageLeft = 400;
constexpr float kStageRight = 880;