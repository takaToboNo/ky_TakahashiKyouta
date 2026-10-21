#include "WalkerEnemy.h"
#include "Bullet.h"
#include "Player.h"

#include <cassert>
#include "DxLib.h"
#include "Camera.h"
#include "MathHelper.h"

void WalkerEnemy::Initialize()
{
	Enemy::Initialize();
	m_Position = { 500.0f,650.0f };
	m_Scale = { WALKER_ENEMY_SIZE,WALKER_ENEMY_SIZE };
	m_Color = { 100, 0, 0 };
	m_Hp = 1;
	m_IsGround = false;
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

	//速度制限Y
	m_Velocity.y = math_helper::clamp(m_Velocity.y, -MAX_FALL_SPEED, MAX_FALL_SPEED);

	//座標更新
	m_Position += m_Velocity * dt;

	m_IsGround = false;

	//プール状態にする
	if (m_Hp <= 0)
	{
		m_IsActive = false;
	}
}

void WalkerEnemy::Draw(const Camera& camera)
{
	const Vector2& pos = camera.GetPosition();
	const float CAMERA_MARGIN = 100.0f;

	if (m_Position.y >= pos.y - CAMERA_MARGIN && m_Position.y <= pos.y + WINDOW_HEIGHT + CAMERA_MARGIN)
	{
		int x1, y1;
		x1 = static_cast<int>(m_Position.x - (m_Scale.x * 0.5f) - pos.x);
		y1 = static_cast<int>(m_Position.y - (m_Scale.y * 0.5f) - pos.y);
		int x2, y2;
		x2 = static_cast<int>(m_Position.x + (m_Scale.x * 0.5f) - pos.x);
		y2 = static_cast<int>(m_Position.y + (m_Scale.y * 0.5f) - pos.y);

		DrawBox(x1, y1, x2, y2, GetColor(RED.r, RED.g, RED.b), TRUE);
	}

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
	HitSide hitSide = other->GetHitSide(hitInfo);

	if (tag == Tag::Block)
	{
		if (hitSide == HitSide::Top)
		{
			m_Velocity.y = 0.0f;
		}
		else if (hitSide == HitSide::Bottom)
		{
			m_Velocity.y = 0.0f;
		}
		else if (hitSide == HitSide::Left)
		{
			m_Velocity.x = 0.0f;
		}
		else if (hitSide == HitSide::Right)
		{
			m_Velocity.x = 0.0f;
		}

		m_IsGround = true;
		m_Position -= hitInfo.normal * hitInfo.depth;
	}

	if (tag == Tag::Bullet)
	{
		assert(dynamic_cast<Bullet*>(other));
		if (!dynamic_cast<Bullet*>(other)) return;

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
