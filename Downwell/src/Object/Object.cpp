#include "Object.h"

void Object::Initialize()
{
	m_Tag = Tag::None;
	m_Layer = Layer::None;
	m_Position = Vector2::Zero();
	m_OldPosition = Vector2::Zero();
	m_IsActive = true;
}

void Object::Finalize()
{
}

void Object::Update(float dt)
{
	m_OldPosition = m_Position;
}

void Object::Destroy()
{
}