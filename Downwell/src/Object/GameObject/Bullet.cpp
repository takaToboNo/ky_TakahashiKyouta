#include "Bullet.h"

//仮
#include "DxLib.h"

void Bullet::Initialize()
{
	GameObject::Initialize();
	m_Layer = Layer::Bullet;
	m_Velocity = { 0.0f,BULLET_SPEED };
	m_Life = 0.0f;
	m_Damage = 0;

	m_Position = { 200.0f,200.0f };
	m_Scale = { 15.0f,15.0f };
	m_IsActive = true;
}

void Bullet::Finalize()
{
	GameObject::Finalize();
}

void Bullet::Update(float dt)
{
	//速度減衰
	m_Velocity.y *= AIR_DRAG;

	//座標更新
	m_Position += m_Velocity * dt;

	//返却予約(速度が小さいもしくは画面外)
	if(m_Velocity.IsNearlyZero(MIN_SPEED)) m_IsActive = false;
	if (m_Position.y < STAGE_TOP) m_IsActive = false;
	if (m_Position.y > STAGE_BOTTOM) m_IsActive = false;

	//当たり判定
	if (CheckHit())
	{
		Vector2 dir = m_FloatingEnemy->GetPosition() - m_Position;
		dir.Normalize();

		m_IsActive = false;
		m_FloatingEnemy->SetVelocity(dir * KNOCK_BACK);
	}
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

bool Bullet::CheckHit()
{
	if (!m_FloatingEnemy) return false;

	//enemy
	float aRight = m_FloatingEnemy->GetPosition().x + m_FloatingEnemy->GetScale().x * 0.5f;
	float aLeft = m_FloatingEnemy->GetPosition().x - m_FloatingEnemy->GetScale().x * 0.5f;
	float aTop = m_FloatingEnemy->GetPosition().y - m_FloatingEnemy->GetScale().y * 0.5f;
	float aBottom = m_FloatingEnemy->GetPosition().y + m_FloatingEnemy->GetScale().y * 0.5f;
	//bullet
	float bRight = m_Position.x + m_Scale.x * 0.5f;
	float bLeft = m_Position.x - m_Scale.x * 0.5f;
	float bTop = m_Position.y - m_Scale.y * 0.5f;
	float bBottom = m_Position.y + m_Scale.y * 0.5f;
	
	if (aRight < bLeft || aLeft > bRight || aBottom < bTop || aTop > bBottom) return false;

	return true;
}