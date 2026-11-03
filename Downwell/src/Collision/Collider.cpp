#include "Collider.h"
#include "GameObject.h"

Rect Collider::GetWorldRect() const
{
	Rect rect;
	rect.position = m_Owner->GetPosition();
	rect.oldPosition = m_Owner->GetOldPosition();
	rect.width = m_Owner->GetScale().x;
	rect.height = m_Owner->GetScale().y;
	return rect;
}