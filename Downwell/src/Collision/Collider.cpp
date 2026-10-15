#include "Collider.h"
#include "MathHelper.h"
#include "GameObject.h"

Rect Collider::GetWorldRect() const
{
	Rect rect;
	rect.position = m_Owner->GetPosition();
	rect.width = m_Owner->GetScale().x;
	rect.height = m_Owner->GetScale().y;
	return rect;
}

Circle Collider::GetWorldCircle() const
{
	Circle circle;
	circle.position = m_Owner->GetPosition();
	circle.radius = m_Owner->GetScale().x;
	return circle;
}