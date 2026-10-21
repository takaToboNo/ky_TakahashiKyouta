#include "SolidBlock.h"

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
	const float CAMERA_MARGIN = 100.0f;

	if (m_Position.y >= pos.y - CAMERA_MARGIN && m_Position.y <= pos.y + WINDOW_HEIGHT + CAMERA_MARGIN)
	{
		int x1, y1;
		x1 = static_cast<int>(m_Position.x - (m_Scale.x * 0.5f) - pos.x);
		y1 = static_cast<int>(m_Position.y - (m_Scale.y * 0.5f) - pos.y);
		int x2, y2;
		x2 = static_cast<int>(m_Position.x + (m_Scale.x * 0.5f) - pos.x);
		y2 = static_cast<int>(m_Position.y + (m_Scale.y * 0.5f) - pos.y);

		DrawBox(x1, y1, x2, y2, GetColor(WHITE.r, WHITE.g, WHITE.b), TRUE);
	}
}

void SolidBlock::Destroy()
{
	Block::Destroy();
}

void SolidBlock::OnCollision(GameObject* other, const HitInfo& hitInfo)
{
}
