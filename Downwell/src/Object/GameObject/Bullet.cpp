#include "Bullet.h"

void Bullet::Initialize()
{
	GameObject::Initialize();
	m_Name = "Bullet";
	m_Tag = Tag::Bullet;
	m_Layer = Layer::Bullet;
	m_Velocity = { 0.0f,BULLET_SPEED };
	m_Life = 0.0f;
	m_Damage = 1;

	m_Position = { 200.0f,200.0f };
	m_Scale = { BULLET_SIZE_X,BULLET_SIZE_Y };
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

void Bullet::Draw(Renderer& renderer)
{
	GameObject::Draw(renderer);
}

void Bullet::DrawDebug()
{
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
