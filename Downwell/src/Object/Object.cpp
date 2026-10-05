#include "Object.h"

void Object::Initialize()
{
	m_Tag = Tag::None;
	m_Position = { 0.0f, 0.0f };
	m_IsActive = false;
}

void Object::Finalize()
{
}

void Object::Destroy()
{
}