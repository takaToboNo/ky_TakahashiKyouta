#include "FloatingEnemy.h"

#include <cassert>
#include "DxLib.h"
#include "Player.h"
#include "MathHelper.h"

void FloatingEnemy::Initialize()
{
	Enemy::Initialize();
	m_MoveSpeed = 50.0f;
	m_Position = { 500.0f,300.0f };
	m_Scale = { 30.0f,30.0f };
	m_Color = { 200, 0, 200 };
	m_Hp = 3;
}

void FloatingEnemy::Finalize()
{
	Enemy::Finalize();
}

void FloatingEnemy::Update(float dt)
{
	Enemy::Update(dt);

	//抵抗
	m_Velocity *= 0.98f;

	if (m_pPlayer)
	{
		Vector2 targetDir = m_pPlayer->GetPosition() - m_Position;
		targetDir.Normalize();

		m_Velocity += targetDir * m_MoveSpeed * dt;
	}

	//速度制限
	float speed = m_Velocity.LengthSquared();
	if (speed > MAX_MOVE_SPEED * MAX_MOVE_SPEED)
	{
		m_Velocity.Normalize();
		m_Velocity *= MAX_MOVE_SPEED;
	}

	//座標更新
	m_Position += m_Velocity * dt;

	//プール状態にする
	if (m_Hp <= 0)
	{
		m_IsActive = false;
	}
}

void FloatingEnemy::Draw()
{
	int x1, y1;
	x1 = static_cast<int>(m_Position.x - (m_Scale.x * 0.5f));
	y1 = static_cast<int>(m_Position.y - (m_Scale.y * 0.5f));
	int x2, y2;
	x2 = static_cast<int>(m_Position.x + (m_Scale.x * 0.5f));
	y2 = static_cast<int>(m_Position.y + (m_Scale.y * 0.5f));

	DrawBox(x1, y1, x2, y2, GetColor(m_Color.r, m_Color.g, m_Color.b), FALSE);

#ifdef _DEBUG
	DrawFormatString(10, 700, GetColor(m_Color.r, m_Color.g, m_Color.b), "FloatingEnemyHP : %d", m_Hp);
#endif
}

void FloatingEnemy::Destroy()
{
	Enemy::Destroy();
}

void FloatingEnemy::OnCollision(GameObject* other, const HitInfo& hitInfo)
{
	Tag tag = other->GetTag();
	HitSide hitSide = GetHitSide(hitInfo);

	if (tag == Tag::Bullet)
	{
		assert(dynamic_cast<Bullet*>(other));
		Bullet* bullet = static_cast<Bullet*>(other);
		Damage(bullet->GetDamage());

		m_Velocity = hitInfo.normal * KNOCK_BACK_FORCE * -1.0f;
	}

	if (tag == Tag::Player)
	{
		if (hitSide == HitSide::Top)
		{
			m_IsActive = false;
		}
	}
}

void FloatingEnemy::Move(Vector2& direction)
{
	(void)direction;
}

void FloatingEnemy::Died()
{
}

bool FloatingEnemy::CheckGround()
{
	return false;
}
