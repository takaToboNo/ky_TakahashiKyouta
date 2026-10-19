#include "Bullet.h"

//仮
#include "DxLib.h"
#include "Camera.h"

void Bullet::Initialize()
{
	GameObject::Initialize();
	m_Tag = Tag::Bullet;
	m_Layer = Layer::Bullet;
	m_Velocity = { 0.0f,BULLET_SPEED };
	m_Life = 0.0f;
	m_Damage = 1;

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
	GameObject::Update(dt);

	//速度減衰
	m_Velocity.y *= AIR_DRAG;

	//座標更新
	m_Position += m_Velocity * dt;

	//返却予約(速度が小さいもしくは画面外)
	if(m_Velocity.IsNearlyZero(MIN_SPEED)) m_IsActive = false;
}

void Bullet::Draw(const Camera& camera)
{
	int x1, y1;
	x1 = static_cast<int>(m_Position.x - (m_Scale.x * 0.5f) - camera.GetPosition().x);
	y1 = static_cast<int>(m_Position.y - (m_Scale.y * 0.5f) - camera.GetPosition().y);
	int x2, y2;
	x2 = static_cast<int>(m_Position.x + (m_Scale.x * 0.5f) - camera.GetPosition().x);
	y2 = static_cast<int>(m_Position.y + (m_Scale.y * 0.5f) - camera.GetPosition().y);

	DrawBox(x1, y1, x2, y2, GetColor(m_Color.r, m_Color.g, m_Color.b), TRUE);
}

void Bullet::Destroy()
{
	GameObject::Destroy();
}

void Bullet::OnCollision(GameObject* other, const HitInfo& hitInfo)
{
	Tag tag = other->GetTag();

	if (tag == Tag::Enemy || tag == Tag::Block)
	{
		m_IsActive = false;
	}
}
