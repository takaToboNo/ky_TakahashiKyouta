#include "BreakableBlock.h"

//‰¼
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
}

void BreakableBlock::Draw(const Camera& camera)
{
	const Vector2& pos = camera.GetPosition();
	const float CAMERA_MARGIN = 100.0f;

	if (m_Position.y >= pos.y - CAMERA_MARGIN && m_Position.y <= pos.y + WINDOW_HEIGHT + CAMERA_MARGIN)
	{
		int x1, y1;
		x1 = static_cast<int>(m_Position.x - (m_Scale.x * 0.5f) - pos.x);
		y1 = static_cast<int>(m_Position.y - (m_Scale.y * 0.5f) - pos.y);
		int x2, y2;
		x2 = static_cast<int>(m_Position.x + (m_Scale.x * 0.5f) - pos.x);
		y2 = static_cast<int>(m_Position.y + (m_Scale.y * 0.5f) - pos.y);

		DrawBox(x1, y1, x2, y2, GetColor(WHITE.r, WHITE.g, WHITE.b), FALSE);
	}
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
			m_IsActive = false;
		}
	}

	if (tag == Tag::Bullet)
	{
		if (hitSide == HitSide::Top)
		{
			m_IsActive = false;
		}
	}
}
