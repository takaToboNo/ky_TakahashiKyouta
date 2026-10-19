#include "GameObject.h"

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

HitSide GameObject::GetHitSide(const HitInfo& hitInfo)
{
	HitSide hitSide;
	if (std::abs(hitInfo.normal.x) > std::abs(hitInfo.normal.y))
	{
		hitSide = (hitInfo.normal.x > 0.0f) ? HitSide::Right : HitSide::Left;
	}
	else
	{
		hitSide = (hitInfo.normal.y > 0.0f) ? HitSide::Bottom : HitSide::Top;
	}
	return hitSide;
}
