#include "WalkerEnemy.h"
#include "Bullet.h"
#include "Player.h"

#include <cassert>
#include "DxLib.h"

void WalkerEnemy::Initialize()
{
	Enemy::Initialize();
	m_Position = { 500.0f,650.0f };
	m_Scale = { 30.0f,30.0f };
	m_Color = { 100, 0, 0 };
	m_Hp = 1;
}

void WalkerEnemy::Finalize()
{
	Enemy::Finalize();
}

void WalkerEnemy::Update(float dt)
{
	Enemy::Update(dt);

	//重力
	m_Velocity.y += FALL_GRAVITY * dt;

	//座標更新
	m_Position += m_Velocity * dt;

	//床接地
	if (m_Position.y >= STAGE_BOTTOM)
	{
		m_Position.y = STAGE_BOTTOM;
		m_Velocity.y = 0.0f;
	}

	//プール状態にする
	if (m_Hp <= 0)
	{
		m_IsActive = false;
	}
}

void WalkerEnemy::Draw()
{
	int x1, y1;
	x1 = static_cast<int>(m_Position.x - (m_Scale.x * 0.5f));
	y1 = static_cast<int>(m_Position.y - (m_Scale.y * 0.5f));
	int x2, y2;
	x2 = static_cast<int>(m_Position.x + (m_Scale.x * 0.5f));
	y2 = static_cast<int>(m_Position.y + (m_Scale.y * 0.5f));

	DrawBox(x1, y1, x2, y2, GetColor(RED.r, RED.g, RED.b), TRUE);

#ifdef _DEBUG
	DrawFormatString(10, 680, GetColor(RED.r, RED.g, RED.b), "WalkerEnemyHP : %d", m_Hp);
#endif
}

void WalkerEnemy::Destroy()
{
	Enemy::Destroy();
}

void WalkerEnemy::OnCollision(GameObject* other, const HitInfo& hitInfo)
{
	Tag tag = other->GetTag();

	if (tag == Tag::Bullet)
	{
		assert(dynamic_cast<Bullet*>(other));
		Bullet* bullet = static_cast<Bullet*>(other);
		Damage(bullet->GetDamage());
	}
}

void WalkerEnemy::Move(Vector2& direction)
{
	(void)direction;
}

void WalkerEnemy::Died()
{
}

bool WalkerEnemy::CheckGround()
{
	return false;
}
