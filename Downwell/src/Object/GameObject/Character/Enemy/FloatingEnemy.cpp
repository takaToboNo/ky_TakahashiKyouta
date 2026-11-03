#include "FloatingEnemy.h"
#include "AudioManager.h"
#include "imgui.h"

#include <cassert>
#include "DxLib.h"
#include "Camera.h"
#include "Player.h"

void FloatingEnemy::Initialize()
{
	Enemy::Initialize();
	m_Name = "FloatingEnemy";
	m_MoveSpeed = 50.0f;
	m_Scale = { FLOATING_ENEMY_SIZE_X,FLOATING_ENEMY_SIZE_Y };
	m_Hp = FLOATING_ENEMY_MAX_HP;
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

	//死亡
	if (m_Hp <= 0 && !m_IsDead)
	{
		AudioManager::GetInstance().PlaySE("EnemyDead");
		m_IsDead = true;
	}

	//死んでいるならプール状態
	if (m_IsDead)
	{
		m_IsActive = false;
	}
}

void FloatingEnemy::Draw(const Camera& camera)
{
	const Vector2& pos = camera.GetPosition();

	int x1, y1;
	x1 = static_cast<int>(m_Position.x - (m_Scale.x * 0.5f) - pos.x);
	y1 = static_cast<int>(m_Position.y - (m_Scale.y * 0.5f) - pos.y);
	int x2, y2;
	x2 = static_cast<int>(m_Position.x + (m_Scale.x * 0.5f) - pos.x);
	y2 = static_cast<int>(m_Position.y + (m_Scale.y * 0.5f) - pos.y);

	DrawBox(x1, y1, x2, y2, GetColor(m_Color.r, m_Color.g, m_Color.b), FALSE);
}

void FloatingEnemy::DrawDebug()
{
	ImGui::Text("Position : (%.2f, %.2f)", m_Position.x, m_Position.y);
	ImGui::Text("Velocity : (%.2f, %.2f)", m_Velocity.x, m_Velocity.y);

	ImGui::Text("IsActive : %s", m_IsActive ? "true" : "false");
	ImGui::Text("IsDead : %s", m_IsDead ? "true" : "false");
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
		if (!dynamic_cast<Bullet*>(other)) return;

		Bullet* bullet = static_cast<Bullet*>(other);
		Damage(bullet->GetDamage());

		m_Velocity = hitInfo.normal * DAMAGE_KNOCKBACK * -1.0f;
	}

	if (tag == Tag::Player)
	{
		if (hitSide == HitSide::Top)
		{
			m_Hp = 0;
		}
	}

	if (tag == Tag::Block)
	{
		m_Velocity = hitInfo.normal * NORMAL_KNOCKBACK * -1.0f;
	}

	if (tag == Tag::Enemy)
	{
		m_Velocity = hitInfo.normal * NORMAL_KNOCKBACK * -1.0f;
	}
}

void FloatingEnemy::Damage(int damage)
{
	AudioManager::GetInstance().PlaySE("EnemyHit");
	m_Hp -= damage;
}

void FloatingEnemy::Activate()
{
	Character::Activate();
	m_Hp = FLOATING_ENEMY_MAX_HP;
}
