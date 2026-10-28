#pragma once
#include "Shape.h"

class GameObject;

enum class HitSide
{	//Ž©•ª‚©‚çŒ©‚Ä‘ŠŽè‚ª‚¢‚éˆÊ’u
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