#include "FloatingEnemy.h"

#include "DxLib.h"

void FloatingEnemy::Initialize()
{
	Enemy::Initialize();
	m_Position = { 500.0f,300.0f };
	m_Scale = { 40.0f,40.0f };
	m_Color = { 200, 0, 200 };
}

void FloatingEnemy::Finalize()
{
	Enemy::Finalize();
}

void FloatingEnemy::Update()
{
}

void FloatingEnemy::Draw()
{
	int x1, y1;
	x1 = static_cast<int>(m_Position.x - (m_Scale.x * 0.5f));
	y1 = static_cast<int>(m_Position.y - (m_Scale.y * 0.5f));
	int x2, y2;
	x2 = static_cast<int>(m_Position.x + (m_Scale.x * 0.5f));
	y2 = static_cast<int>(m_Position.y + (m_Scale.y * 0.5f));

	DrawBox(x1, y1, x2, y2, GetColor(m_Color.r, m_Color.g, m_Color.b), TRUE);
}

void FloatingEnemy::Destroy()
{
	Enemy::Destroy();
}

void FloatingEnemy::Move(Vector2& direction)
{
	(void)direction;
}

void FloatingEnemy::Damage(int damage)
{
	(void)damage;
}

void FloatingEnemy::Died()
{
}

bool FloatingEnemy::CheckGround()
{
	return false;
}
