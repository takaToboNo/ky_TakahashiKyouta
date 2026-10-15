#pragma once
#include "Shape.h"

class GameObject;

enum class HitSide
{	//Ž©•ª‚©‚çŒ©‚Ä‘ŠŽè‚ª‚¢‚éˆÊ’u
	Left,
	Right,
	Top,
	Bottom,
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
	ShapeType m_ShapeType = ShapeType::Rect;

public:
	Collider() = default;
	~Collider() = default;

	ShapeType GetShapeType() const { return m_ShapeType; }

	Rect GetWorldRect() const;
	Circle GetWorldCircle() const;
	void SetOwner(GameObject* owner) { m_Owner = owner; }
};