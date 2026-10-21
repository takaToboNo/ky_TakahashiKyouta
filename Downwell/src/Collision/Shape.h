#pragma once
#include "Vector2.h"

struct Rect
{
	Vector2 position = Vector2::Zero();
	Vector2 oldPosition = Vector2::Zero();
	float width = 0.0f;
	float height = 0.0f;
};