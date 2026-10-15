#pragma once
#include "Vector2.h"

enum class ShapeType
{
	Rect,
	Circle,
};

struct Rect
{
	Vector2 position;
	float width;
	float height;
};

struct Circle
{
	Vector2 position;
	float radius;
};