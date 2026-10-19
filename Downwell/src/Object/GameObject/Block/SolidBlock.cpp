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
	int x1, y1;
	x1 = static_cast<int>(m_Position.x - (m_Scale.x * 0.5f) - camera.GetPosition().x);
	y1 = static_cast<int>(m_Position.y - (m_Scale.y * 0.5f) - camera.GetPosition().y);
	int x2, y2;
	x2 = static_cast<int>(m_Position.x + (m_Scale.x * 0.5f) - camera.GetPosition().x);
	y2 = static_cast<int>(m_Position.y + (m_Scale.y * 0.5f) - camera.GetPosition().y);

	DrawBox(x1, y1, x2, y2, GetColor(WHITE.r, WHITE.g, WHITE.b), TRUE);
}

void SolidBlock::Destroy()
{
	Block::Destroy();
}

void SolidBlock::OnCollision(GameObject* other, const HitInfo& hitInfo)
{
}
