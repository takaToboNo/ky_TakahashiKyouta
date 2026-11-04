#include "SolidBlock.h"
#include "AudioManager.h"

void SolidBlock::Initialize()
{
	Block::Initialize();
	m_Name = "SolidBlock";
}

void SolidBlock::Finalize()
{
	Block::Finalize();
}

void SolidBlock::Update(float dt)
{
	Block::Update(dt);
}

void SolidBlock::Draw(Renderer& renderer)
{
	GameObject::Draw(renderer);
}

void SolidBlock::DrawDebug()
{
}

void SolidBlock::Destroy()
{
	Block::Destroy();
}

void SolidBlock::OnCollision(GameObject* other, const HitInfo& hitInfo)
{
	Tag tag = other->GetTag();
	HitSide hitSide = GetHitSide(hitInfo);

	if (tag == Tag::Bullet)
	{
		AudioManager::GetInstance().PlaySE("BlockHit");
	}
}
