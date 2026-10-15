#include "Character.h"

void Character::Initialize()
{
	GameObject::Initialize();
	m_Hp = 1;
	m_MaxHp = 1;
	m_MoveSpeed = 1.0f;
	m_Velocity = { 0.0f,0.0f };
	m_IsFacingRight = true;
}

void Character::Finalize()
{
	GameObject::Finalize();
}

void Character::Update(float dt)
{
	GameObject::Update(dt);
}

void Character::Destroy()
{
	GameObject::Destroy();
}
