#include "FloatingEnemy.h"

#include "DxLib.h"
#include <cassert>

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
	float x1, y1;
	x1 = m_Position.x - (m_Scale.x * 0.5f);
	y1 = m_Position.y - (m_Scale.y * 0.5f);
	float x2, y2;
	x2 = m_Position.x + (m_Scale.x * 0.5f);
	y2 = m_Position.y + (m_Scale.y * 0.5f);

	int result = DrawBox(x1, y1, x2, y2, GetColor(m_Color.r, m_Color.g, m_Color.b), TRUE);

	assert(result == 0);
}

void FloatingEnemy::Destroy()
{
	Enemy::Destroy();
}

void FloatingEnemy::Move(Vector2& direction)
{
}

void FloatingEnemy::Damage(int damage)
{
}

void FloatingEnemy::Died()
{
}

bool FloatingEnemy::CheckGround()
{
	return false;
}
