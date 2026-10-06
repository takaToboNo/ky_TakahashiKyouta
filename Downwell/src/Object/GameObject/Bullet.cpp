#include "Bullet.h"

//âº
#include <cassert>
#include "Main.h"

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

	m_Velocity.x = 1000.0f;

	//ç¿ïWçXêV
	m_Position += m_Velocity * dt;

	//ï‘ãpó\ñÒ
	if (m_Position.x < 0.0f) m_IsActive = false;
	if (m_Position.x > 1200.0f) m_IsActive = false;
}

void Bullet::Draw()
{
	float x1, y1;
	x1 = m_Position.x - (m_Scale.x * 0.5f);
	y1 = m_Position.y - (m_Scale.y * 0.5f);
	float x2, y2;
	x2 = m_Position.x + (m_Scale.x * 0.5f);
	y2 = m_Position.y + (m_Scale.y * 0.5f);

	int result = DrawBox(x1, y1, x2, y2, GetColor(255, 255, 255), TRUE);

	assert(result == 0);
}

void Bullet::Destroy()
{
	GameObject::Destroy();
}
