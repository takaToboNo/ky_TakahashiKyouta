#include "AmmoGauge.h"
#include "GameHelper.h"
#include "GunBoots.h"
#include "DxLib.h"

void AmmoGauge::Initialize()
{
	m_Scale = { 30.0f,40.0f };
	m_Color = WHITE;

	m_Position = { STAGE_RIGHT + 100.0f, MAX_AMMO * m_Scale.y + 100.0f };
}

void AmmoGauge::Finalize()
{
}

void AmmoGauge::Update(float dt)
{
}

void AmmoGauge::Draw()
{
	for (int i = 0; i < m_GunBoots->GetAmmo(); i++)
	{
		int x1, y1;
		x1 = static_cast<int>(m_Position.x - (m_Scale.x * 0.5f));
		y1 = static_cast<int>(m_Position.y - (m_Scale.y * 0.5f) - (i * (m_Scale.y + 1.0f)));
		int x2, y2;
		x2 = static_cast<int>(m_Position.x + (m_Scale.x * 0.5f));
		y2 = static_cast<int>(m_Position.y + (m_Scale.y * 0.5f) - (i * (m_Scale.y + 1.0f)));

		DrawBox(x1, y1, x2, y2, GetColor(m_Color.r, m_Color.g, m_Color.b), TRUE);
	}

	const int HP_GAUGE_MARGIN = 3;	//ògï`âÊÇè≠ÇµëÂÇ´ÇﬂÇ…Ç∑ÇÈÇΩÇﬂÇÃíl
	int x1 = static_cast<int>(m_Position.x - (m_Scale.x * 0.5f)) - HP_GAUGE_MARGIN;
	int y1 = static_cast<int>(m_Position.y + (m_Scale.y * 0.5f) - (MAX_AMMO * (m_Scale.y + 1.0f))) - HP_GAUGE_MARGIN;
	int x2 = static_cast<int>(m_Position.x + (m_Scale.x * 0.5f)) + HP_GAUGE_MARGIN;
	int y2 = static_cast<int>(m_Position.y + (m_Scale.y * 0.5f)) + HP_GAUGE_MARGIN;
	DrawBox(x1, y1, x2, y2, GetColor(RED.r, RED.g, RED.b), FALSE);

	//ílï`âÊ
	int x = static_cast<int>(m_Position.x) - 5;
	int y = static_cast<int>(m_Position.y + (m_Scale.y * 0.5f)) + 10;
	DrawFormatString(x, y, GetColor(WHITE.r, WHITE.g, WHITE.b), "%d", m_GunBoots->GetAmmo());
}

void AmmoGauge::Destroy()
{
}
