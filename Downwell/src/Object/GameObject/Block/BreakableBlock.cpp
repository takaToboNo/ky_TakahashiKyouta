#include "BreakableBlock.h"
#include "AudioManager.h"

void BreakableBlock::Initialize()
{
	Block::Initialize();
	m_Name = "BreakableBlock";
	m_IsFill = false;
}

void BreakableBlock::Finalize()
{
	Block::Finalize();
}

void BreakableBlock::Update(float dt)
{
	Block::Update(dt);

	if (m_IsDead)
	{
		m_IsActive = false;
	}
}

void BreakableBlock::Draw(Renderer& renderer)
{
	GameObject::Draw(renderer);
}

void BreakableBlock::DrawDebug()
{
}

void BreakableBlock::Destroy()
{
	Block::Destroy();
}

void BreakableBlock::OnCollision(GameObject* other, const HitInfo& hitInfo)
{
	Tag tag = other->GetTag();
	HitSide hitSide = GetHitSide(hitInfo);

	if (tag == Tag::Player)
	{
		if (hitSide == HitSide::Bottom)
		{
			AudioManager::GetInstance().PlaySE("BlockBreak");
			m_IsDead = true;
		}
	}

	if (tag == Tag::Bullet)
	{
		if (hitSide == HitSide::Top)
		{
			AudioManager::GetInstance().PlaySE("BlockBreak");
			m_IsDead = true;
		}
	}
}
