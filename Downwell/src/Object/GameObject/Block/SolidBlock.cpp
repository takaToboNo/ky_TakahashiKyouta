#include "SolidBlock.h"
#include "AudioManager.h"

//‰¼
#include "DxLib.h"
#include "Camera.h"

void SolidBlock::Initialize()
{
	Block::Initialize();
}

void SolidBlock::Finalize()
{
	Block::Finalize();
}

void SolidBlock::Update(float dt)
{
	Block::Update(dt);
}

void SolidBlock::Draw(const Camera& camera)
{
	const Vector2& pos = camera.GetPosition();

	int x1, y1;
	x1 = static_cast<int>(m_Position.x - (m_Scale.x * 0.5f) - pos.x);
	y1 = static_cast<int>(m_Position.y - (m_Scale.y * 0.5f) - pos.y);
	int x2, y2;
	x2 = static_cast<int>(m_Position.x + (m_Scale.x * 0.5f) - pos.x);
	y2 = static_cast<int>(m_Position.y + (m_Scale.y * 0.5f) - pos.y);

	DrawBox(x1, y1, x2, y2, GetColor(m_Color.r, m_Color.g, m_Color.b), TRUE);
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
