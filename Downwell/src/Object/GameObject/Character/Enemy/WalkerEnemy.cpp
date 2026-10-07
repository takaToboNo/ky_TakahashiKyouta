#include "WalkerEnemy.h"

#include "DxLib.h"
#include <cassert>

void WalkerEnemy::Initialize()
{
	Enemy::Initialize();
	m_Position = { 500.0f,650.0f };
	m_Scale = { 50.0f,25.0f };
	m_Color = { 100, 0, 0 };
}

void WalkerEnemy::Finalize()
{
	Enemy::Finalize();
}

void WalkerEnemy::Update()
{
}

void WalkerEnemy::Draw()
{
	int x1, y1;
	x1 = static_cast<int>(m_Position.x - (m_Scale.x * 0.5f));
	y1 = static_cast<int>(m_Position.y - (m_Scale.y * 0.5f));
	int x2, y2;
	x2 = static_cast<int>(m_Position.x + (m_Scale.x * 0.5f));
	y2 = static_cast<int>(m_Position.y + (m_Scale.y * 0.5f));

	DrawBox(x1, y1, x2, y2, GetColor(m_Color.r, m_Color.g, m_Color.b), TRUE);
}

void WalkerEnemy::Destroy()
{
	Enemy::Destroy();
}

void WalkerEnemy::Move(Vector2& direction)
{
	(void)direction;
}

void WalkerEnemy::Damage(int damage)
{
	(void)damage;
}

void WalkerEnemy::Died()
{
}

bool WalkerEnemy::CheckGround()
{
	return false;
}
