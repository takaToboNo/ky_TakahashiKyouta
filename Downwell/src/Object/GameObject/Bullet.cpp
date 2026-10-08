#include "Bullet.h"

//âº
#include <cassert>
#include "DxLib.h"

void Bullet::Initialize()
{
	GameObject::Initialize();
	m_Velocity = { 0.0f,0.0f };
	m_Life = 0.0f;
	m_Damage = 0;

	m_Position = { 200.0f,200.0f };
	m_Scale = { 20.0f,20.0f };
	m_IsActive = true;
}

void Bullet::Finalize()
{
	GameObject::Finalize();
}

void Bullet::Update()
{
	float dt = 1.0f / 60.0f;

	m_Velocity.y = BULLET_SPEED;

	//ç¿ïWçXêV
	m_Position += m_Velocity * dt;

	//ï‘ãpó\ñÒ
	if (m_Position.y < STAGE_TOP) m_IsActive = false;
	if (m_Position.y > STAGE_BOTTOM) m_IsActive = false;
}

void Bullet::Draw()
{
	int x1, y1;
	x1 = static_cast<int>(m_Position.x - (m_Scale.x * 0.5f));
	y1 = static_cast<int>(m_Position.y - (m_Scale.y * 0.5f));
	int x2, y2;
	x2 = static_cast<int>(m_Position.x + (m_Scale.x * 0.5f));
	y2 = static_cast<int>(m_Position.y + (m_Scale.y * 0.5f));

	DrawBox(x1, y1, x2, y2, GetColor(m_Color.r, m_Color.g, m_Color.b), TRUE);
}

void Bullet::Destroy()
{
	GameObject::Destroy();
}
