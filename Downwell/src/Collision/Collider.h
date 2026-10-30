#pragma once
#include "Shape.h"

class GameObject;

enum class HitSide
{	//自分から見て相手がいる位置
	Left = 0,
	Right,
	Top,
	Bottom,
	Max
};

struct HitInfo
{
	Vector2 diff = Vector2::Zero();
	Vector2 normal = Vector2::Zero();
	float depth = 0.0f;
};

class Collider
{
private:
	GameObject* m_Owner = nullptr;

public:
	Collider() = default;
	~Collider() = default;

	Rect GetWorldRect() const;
	void SetOwner(GameObject* owner) { m_Owner = owner; }
};