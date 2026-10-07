#include "GameObject.h"

void GameObject::Initialize()
{
	Object::Initialize();
	m_Scale = { 1.0f,1.0f };
	m_Color = kWhite;
}

void GameObject::Finalize()
{
	Object::Finalize();
}

void GameObject::Destroy()
{
	Object::Destroy();
}
