#include "WalkerEnemy.h"

#include "Main.h"

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
	float x1, y1;
	x1 = m_Position.x - (m_Scale.x * 0.5f);
	y1 = m_Position.y - (m_Scale.y * 0.5f);
	float x2, y2;
	x2 = m_Position.x + (m_Scale.x * 0.5f);
	y2 = m_Position.y + (m_Scale.y * 0.5f);

	int result = DrawBox(x1, y1, x2, y2, GetColor(m_Color.r, m_Color.g, m_Color.b), TRUE);

	assert(result == 0);
}

void WalkerEnemy::Destroy()
{
	Enemy::Destroy();
}

void WalkerEnemy::Move(Vector2& direction)
{
}

void WalkerEnemy::Damage(int damage)
{
}

void WalkerEnemy::Died()
{
}

bool WalkerEnemy::CheckGround()
{
	return false;
}
