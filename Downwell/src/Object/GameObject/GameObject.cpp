#include "GameObject.h"
#include "GameObjectManager.h"

void GameObject::Initialize()
{
	Object::Initialize();
	m_Scale = { 1.0f,1.0f };
	m_Color = WHITE;
	m_Collider.SetOwner(this);
}

void GameObject::Finalize()
{
	Object::Finalize();
}

void GameObject::Update(float dt)
{
	Object::Update(dt);
}

void GameObject::Draw(const Camera& camera)
{
}

void GameObject::Destroy()
{
	Object::Destroy();
}

HitSide GameObject::GetHitSide(const HitInfo& hitInfo) const
{
	if (std::abs(hitInfo.normal.x) > std::abs(hitInfo.normal.y))
	{
		return (hitInfo.normal.x > 0.0f) ? HitSide::Right : HitSide::Left;
	}
	return (hitInfo.normal.y > 0.0f) ? HitSide::Bottom : HitSide::Top;
}

void GameObject::Activate()
{
	m_IsActive = true;
	m_IsDead = false;
}

void GameObject::Deactivate()
{
	m_Position = Vector2(-1000.0f, -1000.0f);
	m_OldPosition = m_Position;

	m_IsActive = false;
	m_IsDead = false;
}
