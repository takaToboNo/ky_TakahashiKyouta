#include "BreakableBlock.h"
#include "AudioManager.h"

//仮
#include "DxLib.h"
#include "Camera.h"

void BreakableBlock::Initialize()
{
	Block::Initialize();
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

void BreakableBlock::Draw(const Camera& camera)
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
